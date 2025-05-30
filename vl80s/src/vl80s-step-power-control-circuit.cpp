#include    <vl80s.h>
#include    <vl80-sme-signals.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void VL80s::stepPowerControlCircuit(double t, double dt)
{
    // АКБ
    battery->setChargeVoltage(shield_210->getOutputVoltage(Shield_210::N116));
    battery->setLoadCurrent(shield_210->getBatteryCurrent());
    battery->step(t, dt);

    // Распределительный щит 210 питания ЦУ
    shield_210->setInputVoltage(Shield_210::N113, battery->getVoltage());
    // Свзь с секцией 2
    shield_210->setInputVoltage(Shield_210::SME_E62, 0.0); // !!! СМЕ ДОБАВИТЬ !!!
    shield_210->setInputVoltage(Shield_210::SME_E66, 0.0); // !!! СМЕ ДОБАВИТЬ !!!

    // Напряжение от обмотки собственных нужд тягового трансформатора
    shield_210->setVoltageAC(0.0);

    // Общий ток, потребляемый цепями управления
    double Icc = pf(aux_compr_motor->getAncorCurrent()) +
                 pf(aux_compr_motor->getFieldCurrent()) +
                 panel_1->getCurrent() +
                 panel_2->getCurrent() +
                 panel_3->getCurrent() +
                 panel_4->getCurrent() +
                 panel_5->getCurrent() +
                 panel_6->getCurrent() +
                 panel_7->getCurrent() +
                 panel_8->getCurrent() +
                 panel_9->getCurrent() +
                 power_units->getCurrent() +
                 valve_vz104->getCurrent() +
                 valve_kep6->getCurrent();

    shield_210->setLoadCurrent(Icc);
    shield_210->setControl(keys);
    shield_210->step(t, dt);

    // Панель автоматов (щиток 215)
    shield_215->setInputVoltage(Shield_215::N0, shield_210->getOutputVoltage(Shield_210::N0));
    shield_215->setInputVoltage(Shield_215::N119, shield_210->getOutputVoltage(Shield_210::N119));
    shield_215->setInputVoltage(Shield_215::N113, battery->getVoltage());
    shield_215->setControl(keys);
    shield_215->step(t, dt);

    // Панель автоматов (щиток 216)
    shield_216->setInputVoltage(Shield_216::N0, shield_210->getOutputVoltage(Shield_210::N0));
    shield_216->setControl(keys);
    shield_216->step(t, dt);

    // Щиток 223 (дальний "рояль")
    shield_223->setInputVoltage(Shield_223::N01, shield_215->getOutputVoltage(Shield_215::N01));
    shield_223->setInputVoltage(Shield_223::N02, shield_215->getOutputVoltage(Shield_215::N02));
    shield_223->setInputVoltage(Shield_223::N011, shield_215->getOutputVoltage(Shield_215::N011));
    shield_223->setInputVoltage(Shield_223::SME_E16, 0.0); // !!! СМЕ ДОБАВИТЬ !!!
    shield_223->setInputVoltage(Shield_223::SME_E17, 0.0); // !!! СМЕ ДОБАВИТЬ !!!
    shield_223->setControl(keys);
    shield_223->step(t, dt);

    // Щиток 224 (ближний "рояль")
    shield_224->setInputVoltage(Shield_224::N05, shield_215->getOutputVoltage(Shield_215::N05));
    shield_224->setInputVoltage(Shield_224::N09, shield_215->getOutputVoltage(Shield_215::N09));
    shield_224->setInputVoltage(Shield_224::N010, shield_215->getOutputVoltage(Shield_215::N010));
    shield_224->setInputVoltage(Shield_224::N014, shield_215->getOutputVoltage(Shield_215::N014));
    shield_224->setControl(keys);
    shield_224->step(t, dt);

    // Щиток 225 ("рояль" помошника)
    shield_225->setInputVoltage(Shield_225::N012, shield_215->getOutputVoltage(Shield_215::N012));
    shield_225->setInputVoltage(Shield_225::N013, shield_215->getOutputVoltage(Shield_215::N013));
    shield_225->setInputVoltage(Shield_225::N014, shield_215->getOutputVoltage(Shield_215::N014));
    shield_225->setInputVoltage(Shield_225::N033, shield_216->getOutputVoltage(Shield_216::N033));
    shield_225->setControl(keys);
    shield_225->step(t, dt);

    // Щиток 226
    shield_226->setInputVoltage(Shield_226::N010, shield_215->getOutputVoltage(Shield_215::N010));
    shield_226->setInputVoltage(Shield_226::N512, 0.0); // !!! ЗАДАТЬ ПОСЛЕ РЕАЛИЗАЦИИ ВНЕШНЕЙ ЦЕПИ !!!
    shield_226->setInputVoltage(Shield_226::N514, 0.0); // !!! ЗАДАТЬ ПОСЛЕ РЕАЛИЗАЦИИ ВНЕШНЕЙ ЦЕПИ !!!
    shield_226->setControl(keys);
    shield_226->step(t, dt);

    // Щиток 227
    shield_227->setInputVoltage(Shield_227::N010, shield_215->getOutputVoltage(Shield_215::N010));
    shield_227->setInputVoltage(Shield_227::E18, shield_224->getOutputVoltage(Shield_224::E18));
    shield_227->setInputVoltage(Shield_227::N511, 0.0); // !!! ЗАДАТЬ ПОСЛЕ РЕАЛИЗАЦИИ ВНЕШНЕЙ ЦЕПИ !!!
    shield_227->setInputVoltage(Shield_227::N513, 0.0); // !!! ЗАДАТЬ ПОСЛЕ РЕАЛИЗАЦИИ ВНЕШНЕЙ ЦЕПИ !!!
    shield_227->setInputVoltage(Shield_227::N505, 0.0); // !!! ЗАДАТЬ ПОСЛЕ РЕАЛИЗАЦИИ ВНЕШНЕЙ ЦЕПИ !!!
    shield_227->setInputVoltage(Shield_227::N101, 0.0); // !!! ЗАДАТЬ ПОСЛЕ РЕАЛИЗАЦИИ ВНЕШНЕЙ ЦЕПИ !!!
    shield_227->setInputVoltage(Shield_227::N66, shield_210->getOutputVoltage(Shield_210::N66));
    shield_227->setControl(keys);
    shield_227->step(t, dt);

    // Щиток 228
    shield_228->setInputVoltage(Shield_228::N014, shield_215->getOutputVoltage(Shield_215::N014));
    shield_228->setControl(keys);
    shield_228->step(t, dt);

    // Щиток 229
    shield_229->setInputVoltage(Shield_229::N014, shield_215->getOutputVoltage(Shield_215::N014));
    shield_229->setControl(keys);
    shield_229->step(t, dt);

    // Контроллер машиниста
    double U_N1 = shield_223->getOutputVoltage(Shield_223::E1) * static_cast<double>(brake_lock->isUnlocked());
    km->setInputVoltage(ControllerKM84::N1, U_N1);
    km->setInputVoltage(ControllerKM84::N03, shield_215->getOutputVoltage(Shield_215::N03));
    km->setInputVoltage(ControllerKM84::N05, shield_215->getOutputVoltage(Shield_215::N05));
    km->setInputVoltage(ControllerKM84::N88, shield_223->getOutputVoltage(Shield_223::N88));
    km->setInputVoltage(ControllerKM84::N306, 0.0); // !!! ЗАДАТЬ ПОСЛЕ РЕАЛИЗАЦИИ ВНЕШНЕЙ ЦЕПИ !!!

    // Проверяем запрет на включение реверсивки в неактивной кабине
    if ((sme_bwd->getSignal(SME_NO_REVERS_HANDLE) == 1.0) ||
        (sme_bwd->getSignal(SME_NO_REVERS_HANDLE) == 1.0))
    {
        if (km->isReversHandle())
        {
            km->setBrakeHandlePos(BRAKE_POS_0);
            km->setMainHandlePos(POS_0);
            km->setReversHandlePos(REVERS_POS_0);
            km->insertReversHandle(false);
        }
        QMap<int, bool> empty_keys = {};
        km->setControl(empty_keys);
    }
    else
    {
        km->setControl(keys);
    }
    km->step(t, dt);


    // Панель 1
    double U_E38 = max(shield_223->getOutputVoltage(Shield_223::E16),
                       sme_bwd->getSignal(SME_E30_IN));

    panel_1->setInputVoltage(Panel_1::E28_IN, U_E38 * static_cast<double>(pvu1->getState()));
    panel_1->setInputVoltage(Panel_1::E35_IN, sme_bwd->getSignal(SME_E35_IN));
    panel_1->setControl(keys);
    panel_1->step(t, dt);

    // Панель 2
    panel_2->setControl(keys);
    panel_2->step(t, dt);

    panel_3->setControl(keys);
    panel_3->step(t, dt);

    panel_4->setControl(keys);
    panel_4->step(t, dt);

    panel_5->setControl(keys);
    panel_5->step(t, dt);

    panel_6->setControl(keys);
    panel_6->step(t, dt);

    panel_7->setControl(keys);
    panel_7->step(t, dt);

    panel_8->setControl(keys);
    panel_8->step(t, dt);

    double U_E37 = max(sme_bwd->getSignal(SME_E37_IN), panel_1->getOutputVoltage(Panel_1::E28_OUT));
    panel_9->setInputVoltage(Panel_9::E37, U_E37);
    panel_9->setInputVoltage(Panel_9::E16, shield_223->getOutputVoltage(Shield_223::E16));
    panel_9->setControl(keys);
    panel_9->step(t, dt);
}
