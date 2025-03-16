#include    <vl80s.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void VL80s::stepPowerControlCircuit(double t, double dt)
{
    battery->setChargeVoltage(0.0);
    battery->step(t, dt);
}
