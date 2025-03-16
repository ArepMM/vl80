#include    "vl80s.h"

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
void VL80s::stepBrakesEquipment(double t, double dt)
{
    // Тормозная магистраль
    double BP_flow = 0.0;
    BP_flow += brake_lock->getBPflow();

    anglecock_bp_fwd->setHoseFlow(hose_bp_fwd->getFlow());
    BP_flow += anglecock_bp_fwd->getFlowToPipe();

    anglecock_bp_bwd->setHoseFlow(hose_bp_bwd->getFlow());
    BP_flow += anglecock_bp_bwd->getFlowToPipe();

    brakepipe->setFlow(BP_flow);
    brakepipe->step(t, dt);

    // Воздухораспределитель
    air_dist->setBPpressure(brakepipe->getPressure());
    air_dist->setBCpressure(impulse_line->getPressure());
    air_dist->setSRpressure(supply_reservoir->getPressure());
    air_dist->step(t, dt);

    // Запасный резервуар
    supply_reservoir->setFlow(air_dist->getSRflow());
    supply_reservoir->step(t, dt);

    // Тормозные рычажные передачи
    brake_mech[TROLLEY_FWD]->setBCflow(bc_line->getPipeFlow1());
    brake_mech[TROLLEY_FWD]->setAngularVelocity(0, wheel_omega[0]);
    brake_mech[TROLLEY_FWD]->setAngularVelocity(1, wheel_omega[1]);
    brake_mech[TROLLEY_FWD]->step(t, dt);

    brake_mech[TROLLEY_BWD]->setBCflow(bc_pressure_relay->getPipeFlow());
    brake_mech[TROLLEY_BWD]->setAngularVelocity(0, wheel_omega[2]);
    brake_mech[TROLLEY_BWD]->setAngularVelocity(1, wheel_omega[3]);
    brake_mech[TROLLEY_BWD]->step(t, dt);

    Q_r[1] = brake_mech[TROLLEY_FWD]->getBrakeTorque(0);
    Q_r[2] = brake_mech[TROLLEY_FWD]->getBrakeTorque(1);

    Q_r[3] = brake_mech[TROLLEY_BWD]->getBrakeTorque(0);
    Q_r[4] = brake_mech[TROLLEY_BWD]->getBrakeTorque(1);

    // Концевые краны тормозной магистрали
    anglecock_bp_fwd->setPipePressure(brakepipe->getPressure());
    anglecock_bp_fwd->setControl(keys);
    anglecock_bp_fwd->step(t, dt);
    anglecock_bp_bwd->setPipePressure(brakepipe->getPressure());
    anglecock_bp_bwd->setControl(keys);
    anglecock_bp_bwd->step(t, dt);

    // Рукава тормозной магистрали
    hose_bp_fwd->setPressure(anglecock_bp_fwd->getPressureToHose());
    hose_bp_fwd->setFlowCoeff(anglecock_bp_fwd->getFlowCoeff());
    hose_bp_fwd->setCoord(train_coord + dir * orient * (length / 2.0 - anglecock_bp_fwd->getShiftCoord()));
    hose_bp_fwd->setShiftSide(anglecock_bp_fwd->getShiftSide());
    hose_bp_fwd->setControl(keys);
    hose_bp_fwd->step(t, dt);
    hose_bp_bwd->setPressure(anglecock_bp_bwd->getPressureToHose());
    hose_bp_bwd->setFlowCoeff(anglecock_bp_bwd->getFlowCoeff());
    hose_bp_bwd->setCoord(train_coord - dir * orient * (length / 2.0 - anglecock_bp_bwd->getShiftCoord()));
    hose_bp_bwd->setShiftSide(anglecock_bp_bwd->getShiftSide());
    hose_bp_bwd->setControl(keys);
    hose_bp_bwd->step(t, dt);
}
