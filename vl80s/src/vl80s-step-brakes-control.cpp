#include    "vl80s.h"

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
void VL80s::stepBrakesControl(double t, double dt)
{
    // Блокировочное устройство
    brake_lock->setFLpressure(main_reservoir->getPressure());
    brake_lock->setBPpressure(brakepipe->getPressure());
    //brake_lock->setBCpressure(TODO);
    brake_lock->setCraneFLflow(brake_crane->getFLflow() + loco_crane->getFLflow());
    brake_lock->setCraneBPflow(brake_crane->getBPflow());
    brake_lock->setCraneBCflow(loco_crane->getBCflow());
    brake_lock->setControl(keys);
    brake_lock->step(t, dt);

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
    //loco_crane->setILpressure(TODO);

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
}
