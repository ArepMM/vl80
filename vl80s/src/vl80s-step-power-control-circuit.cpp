#include    <vl80s.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void VL80s::stepPowerControlCircuit(double t, double dt)
{
    // АКБ
    battery->setChargeVoltage(shield_210->getOutputVoltage(Shield_210::N116));
    battery->setLoadCurrent(shield_210->getBatteryCurrent());
    battery->step(t, dt);

    // Распределительный щит 210 питания ЦУ
    shield_210->setInputVoltage(Shield_210::N113, battery->getVoltage());
    // Свзь с секцией 2
    shield_210->setInputVoltage(Shield_210::E62, 0.0);
    shield_210->setInputVoltage(Shield_210::E66, 0.0);

    // Напряжение от обмотки собственных нужд тягового трансформатора
    shield_210->setVoltageAC(0.0);

    shield_210->setLoadCurrent(10.0);
    shield_210->step(t, dt);

    // Панель автоматов (щиток 215)
    shield_215->setInputVoltage(Shield_215::N0, shield_210->getOutputVoltage(Shield_210::N0));
    shield_215->setInputVoltage(Shield_215::N119, shield_210->getOutputVoltage(Shield_210::N119));
    shield_215->step(t, dt);

    // Щиток 223 (дальний "рояль")
    shield_223->setInputSignal(Shield_223::N01, shield_215->getOutputSignal(Shield_215::N01));
    shield_223->step(t, dt);

    // Контроллер машиниста
    km->setControl(keys);
    km->step(t, dt);
}
