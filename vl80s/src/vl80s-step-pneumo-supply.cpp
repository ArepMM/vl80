#include    "vl80s.h"

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
void VL80s::stepPneumoSupply(double t, double dt)
{
    // ПВУ7 - контроль давления в резервуаре управления
    // (считаем резервуар управления и резервуар главного выключателя
    // единым целым)
    pvu7->setPressure(switch_reservoir->getPressure());
    pvu7->step(t, dt);

    // Питание на контактор 135 через тумблер "Компрессор токоприемника"
    // и замыкающие контакты ПВУ7
    double U_N134 = shield_227->getOutputVoltage(Shield_227::N67) *
                    static_cast<double>(pvu7->getState());
    K135->setVoltage(U_N134);
    K135->step(t, dt);

    // Питание на двигатель через контактор 135
    double U_aux_compr = shield_210->getOutputVoltage(Shield_210::N66) *
                         static_cast<double>(K135->getContactState(K135_ON_AUX_COMPRESSOR));

    aux_compr_motor->setAncorVoltage(U_aux_compr);
    aux_compr_motor->setAncorOmega(aux_compr->getOmega());
    aux_compr_motor->step(t, dt);

    // Вспомогательный компрессор токоприёмника
    aux_compr->setActorTorque(aux_compr_motor->getTorquie());
    aux_compr->setOutputPressure(switch_reservoir->getPressure());
    aux_compr->step(t, dt);

    // Поток воздуха из ПМ в резервуар управления клапан
    double K_pm_aux = 4e-3;
    double Q_pm_aux = K_pm_aux * pf(main_reservoir->getPressure() - switch_reservoir->getPressure());
    // Потоки воздуха в резервуар управления
    double Q_aux = aux_compr->getQ_out() + Q_pm_aux + pneumoreducer_pant->getInputFlow();

    // Резервуар главного выключателя
    switch_reservoir->setFlow(Q_aux);
    switch_reservoir->step(t, dt);

    // Пневморедуктор к резервуару токоприёмника
    pneumoreducer_pant->setInputPressure(switch_reservoir->getPressure());
    pneumoreducer_pant->setOutFlow(shutoff_pant->getFlowToPipe() + valve_vz104->getFlowToPipe());
    pneumoreducer_pant->step(t, dt);

    // Разобщительный кран резервуара токоприёмника
    double K_aux_pant = 4e-3;
    double Q_aux_pant = K_aux_pant * (shutoff_pant->getPressureToDevice() - pant_reservoir->getPressure());
    shutoff_pant->setPipePressure(pneumoreducer_pant->getOutPressure());
    shutoff_pant->setDeviceFlow(-Q_aux_pant);
    shutoff_pant->setControl(keys);
    shutoff_pant->step(t, dt);

    // Резервуар токоприемника
    pant_reservoir->setFlow(Q_aux_pant);
    pant_reservoir->step(t, dt);

    // Вентиль защиты ВЗ
    valve_vz104->setPipePressure(pneumoreducer_pant->getOutPressure());
    valve_vz104->setDeviceFlow(valve_kep6->getFlowToPipe());
    valve_vz104->setVoltage(power_units->getOutputVoltage(PowerUnit::N44)); // TODO
    valve_vz104->step(t, dt);

    // Вентиль токоприёмника КЭП6
    valve_kep6->setPipePressure(valve_vz104->getPressureToDevice());
    valve_kep6->setDeviceFlow(pantograph->getPneumodriveFlow());
    valve_kep6->setVoltage(50.0 * shield_223->getTumblerPos(Shield_223::TUMBLER_PANT_FWD)); // TODO
    valve_kep6->step(t, dt);

    // ПВУ1 - контроль давления в магистрали пневмоблокировок и токоприёмника
    pvu1->setPressure(valve_vz104->getPressureToDevice());
    pvu1->step(t, dt);


    // Регулятор давления в главных резервуарах
    press_reg->setFLpressure(main_reservoir->getPressure());
    press_reg->step(t, dt);

    // Мотор-компрессор
    double U_power = 0.0;//380.0 * press_reg->getState(); // TODO
    motor_compressor->setFLpressure(main_reservoir->getPressure());
    motor_compressor->setPowerVoltage(U_power);
    motor_compressor->step(t, dt);

    // Питательная магистраль
    double FL_flow = 0.0;
    FL_flow += motor_compressor->getFLflow();
    FL_flow += brake_lock->getFLflow();
    FL_flow += bc_pressure_relay->getFLflow();

    anglecock_fl_fwd->setHoseFlow(hose_fl_fwd->getFlow());
    FL_flow += anglecock_fl_fwd->getFlowToPipe();

    anglecock_fl_bwd->setHoseFlow(hose_fl_bwd->getFlow());
    FL_flow += anglecock_fl_bwd->getFlowToPipe();

    FL_flow -= Q_pm_aux;

    main_reservoir->setFlow(FL_flow);
    main_reservoir->step(t, dt);

    // Концевые краны питательной магистрали
    anglecock_fl_fwd->setPipePressure(main_reservoir->getPressure());
    anglecock_fl_fwd->setControl(keys);
    anglecock_fl_fwd->step(t, dt);
    anglecock_fl_bwd->setPipePressure(main_reservoir->getPressure());
    anglecock_fl_bwd->setControl(keys);
    anglecock_fl_bwd->step(t, dt);

    // Рукава питательной магистрали
    hose_fl_fwd->setPressure(anglecock_fl_fwd->getPressureToHose());
    hose_fl_fwd->setFlowCoeff(anglecock_fl_fwd->getFlowCoeff());
    hose_fl_fwd->setCoord(train_coord + dir * orient * (length / 2.0 - anglecock_fl_fwd->getShiftCoord()));
    hose_fl_fwd->setShiftSide(anglecock_fl_fwd->getShiftSide());
    hose_fl_fwd->setControl(keys);
    hose_fl_fwd->step(t, dt);
    hose_fl_bwd->setPressure(anglecock_fl_bwd->getPressureToHose());
    hose_fl_bwd->setFlowCoeff(anglecock_fl_bwd->getFlowCoeff());
    hose_fl_bwd->setCoord(train_coord - dir * orient * (length / 2.0 - anglecock_fl_bwd->getShiftCoord()));
    hose_fl_bwd->setShiftSide(anglecock_fl_bwd->getShiftSide());
    hose_fl_bwd->setControl(keys);
    hose_fl_bwd->step(t, dt);
}
