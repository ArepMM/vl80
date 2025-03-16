#include    <vl80s.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void VL80s::stepPowerControlCircuit(double t, double dt)
{
    // АКБ
    battery->setChargeVoltage(0.0);
    battery->step(t, dt);

    // Распределительный щит 210 питания ЦУ
    shield_210->setInputVoltage(S210_N113, battery->getVoltage());
    // Свзь с секцией 2
    shield_210->setInputVoltage(S210_E62, 0.0);
    shield_210->setInputVoltage(S210_E66, 0.0);
    shield_210->step(t, dt);

    // Панель автоматов (щиток 215)
    shield_215->setInputVoltage(S215_N0, shield_210->getOutputVoltage(S210_N0));
    shield_215->setInputVoltage(S215_N119, shield_210->getOutputVoltage(S210_N119));
    shield_215->step(t, dt);
}
