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
