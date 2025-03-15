#include    "vl80s.h"

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
void VL80s::stepPneumoSupply(double t, double dt)
{
    // Мотор-компрессор
    press_reg->setFLpressure(main_reservoir->getPressure());
    press_reg->step(t, dt);

    // Мотор-компрессор
    double U_power = 380.0 * press_reg->getState(); // TODO
    motor_compressor->setFLpressure(main_reservoir->getPressure());
    motor_compressor->setPowerVoltage(U_power);
    motor_compressor->step(t, dt);

    // Питательная магистраль
    double FL_flow = 0.0;
    FL_flow += motor_compressor->getFLflow();

    anglecock_fl_fwd->setHoseFlow(hose_fl_fwd->getFlow());
    FL_flow += anglecock_fl_fwd->getFlowToPipe();

    anglecock_fl_bwd->setHoseFlow(hose_fl_bwd->getFlow());
    FL_flow += anglecock_fl_bwd->getFlowToPipe();

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
