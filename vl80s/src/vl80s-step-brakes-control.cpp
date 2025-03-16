#include    "vl80s.h"

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
void VL80s::stepBrakesControl(double t, double dt)
{
    // Блокировочное устройство
    brake_lock->setFLpressure(main_reservoir->getPressure());
    brake_lock->setBPpressure(brakepipe->getPressure());
    brake_lock->setBCpressure(bc_line->getInputPressure());
    brake_lock->setCraneFLflow(brake_crane->getFLflow() + loco_crane->getFLflow());
    brake_lock->setCraneBPflow(brake_crane->getBPflow());
    brake_lock->setCraneBCflow(loco_crane->getBCflow());
    brake_lock->setControl(keys);
    brake_lock->step(t, dt);

    // Импульсная магистраль
    double il_flow = 0.0;
    il_flow += air_dist->getBCflow();
    il_flow += loco_crane->getILflow();

    anglecock_il_bwd->setHoseFlow(hose_il_bwd->getFlow());
    il_flow += anglecock_il_bwd->getFlowToPipe();

    impulse_line->setFlow(il_flow);
    impulse_line->step(t, dt);

    // Поездной кран машиниста
    brake_crane->setFLpressure(brake_lock->getCraneFLpressure());
    brake_crane->setBPpressure(brake_lock->getCraneBPpressure());
    // Управляем краном, учитывая возможное наличие внешнего пульта
    if (control_signals.analogSignal[CS_BRAKE_CRANE].is_active)
    {
        int brake_crane_pos = static_cast<int>(control_signals.analogSignal[CS_BRAKE_CRANE].cur_value);
        brake_crane->setHandlePosition(brake_crane_pos);
    }
    else
    {
        brake_crane->setControl(keys);
    }
    brake_crane->step(t, dt);

    // Кран вспомогательного тормоза
    loco_crane->setFLpressure(brake_lock->getCraneFLpressure());
    loco_crane->setBCpressure(brake_lock->getCraneBCpressure());
    loco_crane->setILpressure(impulse_line->getPressure());
    // Управляем краном, с учетом возможного наличия пульта
    if (control_signals.analogSignal[CS_LOCO_CRANE].is_active)
    {
        double pos = 0.0;

        if (static_cast<bool>(control_signals.analogSignal[CS_RELEASE_VALVE].cur_value))
        {
            loco_crane->release(true);
            pos = -1.0;
        }
        else
        {
            loco_crane->release(false);
            pos = control_signals.analogSignal[CS_LOCO_CRANE].cur_value;
        }

        loco_crane->setHandlePosition(pos);
    }
    else
    {
        loco_crane->setControl(keys);
    }
    loco_crane->step(t, dt);

    // Магистраль тормозных цилиндров
    double bc_flow = 0.0;
    bc_flow += brake_lock->getBCflow();

    anglecock_bc_fwd->setHoseFlow(hose_bc_fwd->getFlow());
    bc_flow += anglecock_bc_fwd->getFlowToPipe();

    anglecock_bc_bwd->setHoseFlow(hose_bc_bwd->getFlow());
    bc_flow += anglecock_bc_bwd->getFlowToPipe();

    bc_line->setInputFlow(bc_flow);
    bc_line->setPipePressure1(brake_mech[TROLLEY_FWD]->getBCpressure());
    bc_line->setPipePressure2(bc_pressure_relay->getControlPressure());
    bc_line->step(t, dt);

    // Повторительное реле давления управляет давлением в ТЦ задней тележки
    bc_pressure_relay->setFLpressure(main_reservoir->getPressure());
    bc_pressure_relay->setControlFlow(bc_line->getPipeFlow2());
    bc_pressure_relay->setPipePressure(brake_mech[TROLLEY_BWD]->getBCpressure());
    bc_pressure_relay->step(t, dt);

    // Концевой кран импульсной магистрали сзади
    anglecock_il_bwd->setPipePressure(impulse_line->getPressure());
    anglecock_il_bwd->setControl(keys);
    anglecock_il_bwd->step(t, dt);

    // Рукав импульсной магистрали сзади
    hose_il_bwd->setPressure(anglecock_il_bwd->getPressureToHose());
    hose_il_bwd->setFlowCoeff(anglecock_il_bwd->getFlowCoeff());
    hose_il_bwd->setCoord(train_coord - dir * orient * (length / 2.0 - anglecock_il_bwd->getShiftCoord()));
    hose_il_bwd->setShiftSide(anglecock_il_bwd->getShiftSide());
    hose_il_bwd->setControl(keys);
    hose_il_bwd->step(t, dt);

    // Концевые краны магистрали тормозных цилиндров
    anglecock_bc_fwd->setPipePressure(bc_line->getInputPressure());
    anglecock_bc_fwd->setControl(keys);
    anglecock_bc_fwd->step(t, dt);

    anglecock_bc_bwd->setPipePressure(bc_line->getInputPressure());
    anglecock_bc_bwd->setControl(keys);
    anglecock_bc_bwd->step(t, dt);

    // Рукава магистрали тормозных цилиндров
    hose_bc_fwd->setPressure(anglecock_bc_fwd->getPressureToHose());
    hose_bc_fwd->setFlowCoeff(anglecock_bc_fwd->getFlowCoeff());
    hose_bc_fwd->setCoord(train_coord + dir * orient * (length / 2.0 - anglecock_bc_fwd->getShiftCoord()));
    hose_bc_fwd->setShiftSide(anglecock_bc_fwd->getShiftSide());
    hose_bc_fwd->setControl(keys);
    hose_bc_fwd->step(t, dt);

    hose_bc_bwd->setPressure(anglecock_bc_bwd->getPressureToHose());
    hose_bc_bwd->setFlowCoeff(anglecock_bc_bwd->getFlowCoeff());
    hose_bc_bwd->setCoord(train_coord - dir * orient * (length / 2.0 - anglecock_bc_bwd->getShiftCoord()));
    hose_bc_bwd->setShiftSide(anglecock_bc_bwd->getShiftSide());
    hose_bc_bwd->setControl(keys);
    hose_bc_bwd->step(t, dt);
}
