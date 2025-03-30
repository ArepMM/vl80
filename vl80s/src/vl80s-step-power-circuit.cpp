#include    <vl80s.h>
#include    <vl80-sme-signals.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void VL80s::stepPowerCircuit(double t, double dt)
{
    // Временно вместо питания от инфраструтуры маршрута
    pantograph->link();
    pantograph->setWireHeight(6.56);
    pantograph->setVoltage(25000.0);
    pantograph->setFrequency(50.0);

    // Пантограф
    pantograph->setPneumodriveRefPressure(valve_kep6->getPressureToDevice());
    pantograph->step(t, dt);
}
