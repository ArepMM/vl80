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

    // Блоки силовых аппаратов
    double U_E15 = max(shield_223->getOutputVoltage(Shield_223::E15),
                       sme_bwd->getSignal(SME_E15_IN));
    power_units->setInputVoltage(PowerUnit::E15, U_E15);

    power_units->step(t, dt);
}
