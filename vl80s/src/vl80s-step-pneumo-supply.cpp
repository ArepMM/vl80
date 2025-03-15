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
    double U_power = 380.0; // TODO
    motor_compressor->setFLpressure(main_reservoir->getPressure());
    motor_compressor->setPowerVoltage(U_power);
    motor_compressor->step(t, dt);

    // Питательная магистраль
    double FL_flow = 0.0;
    FL_flow += motor_compressor->getFLflow();

    main_reservoir->setFlow(FL_flow);
    main_reservoir->step(t, dt);
}
