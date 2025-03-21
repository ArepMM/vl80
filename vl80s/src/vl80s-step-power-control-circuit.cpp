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
    shield_210->setInputVoltage(Shield_210::SME_E62, 0.0); // !!! СМЕ ДОБАВИТЬ !!!
    shield_210->setInputVoltage(Shield_210::SME_E66, 0.0); // !!! СМЕ ДОБАВИТЬ !!!

    // Напряжение от обмотки собственных нужд тягового трансформатора
    shield_210->setVoltageAC(0.0);

    shield_210->setLoadCurrent(10.0);
    shield_210->step(t, dt);

    // Панель автоматов (щиток 215)
    shield_215->setInputVoltage(Shield_215::N0, shield_210->getOutputVoltage(Shield_210::N0));
    shield_215->setInputVoltage(Shield_215::N119, shield_210->getOutputVoltage(Shield_210::N119));
    shield_215->setInputVoltage(Shield_215::N113, battery->getVoltage());
    shield_215->step(t, dt);

    // Панель автоматов (щиток 216)
    shield_216->setInputVoltage(Shield_216::N0, shield_210->getOutputVoltage(Shield_210::N0));
    shield_216->step(t, dt);

    // Щиток 223 (дальний "рояль")
    shield_223->setInputVoltage(Shield_223::N01, shield_215->getOutputVoltage(Shield_215::N01));
    shield_223->setInputVoltage(Shield_223::N02, shield_215->getOutputVoltage(Shield_215::N02));
    shield_223->setInputVoltage(Shield_223::N011, shield_215->getOutputVoltage(Shield_215::N011));
    shield_223->setInputVoltage(Shield_223::SME_E16, 0.0); // !!! СМЕ ДОБАВИТЬ !!!
    shield_223->setInputVoltage(Shield_223::SME_E17, 0.0); // !!! СМЕ ДОБАВИТЬ !!!
    shield_223->setControl(keys);
    shield_223->step(t, dt);

    // Щиток 224 (ближний "рояль")
    shield_224->setInputVoltage(Shield_224::N05, shield_215->getOutputVoltage(Shield_215::N05));
    shield_224->setInputVoltage(Shield_224::N09, shield_215->getOutputVoltage(Shield_215::N09));
    shield_224->setInputVoltage(Shield_224::N010, shield_215->getOutputVoltage(Shield_215::N010));
    shield_224->setControl(keys);
    shield_224->step(t, dt);

    // Щиток 225 ("рояль" помошника)
    shield_225->setInputVoltage(Shield_225::N012, shield_215->getOutputVoltage(Shield_215::N012));
    shield_225->setInputVoltage(Shield_225::N013, shield_215->getOutputVoltage(Shield_215::N013));
    shield_225->setInputVoltage(Shield_225::N014, shield_215->getOutputVoltage(Shield_215::N014));
    shield_225->setInputVoltage(Shield_225::N033, shield_216->getOutputVoltage(Shield_216::N033));
    shield_225->setControl(keys);
    shield_225->step(t, dt);

    // Контроллер машиниста
    double U_N1 = shield_223->getOutputVoltage(Shield_223::E1) * static_cast<double>(brake_lock->isUnlocked());
    km->setInputVoltage(ControllerKM84::N1, U_N1);
    km->setInputVoltage(ControllerKM84::N03, shield_215->getOutputVoltage(Shield_215::N03));
    km->setInputVoltage(ControllerKM84::N05, shield_215->getOutputVoltage(Shield_215::N05));
    km->setInputVoltage(ControllerKM84::N88, shield_223->getOutputVoltage(Shield_223::N88));
    km->setInputVoltage(ControllerKM84::N306, 0.0); // !!! ЗАДАТЬ ПОСЛЕ РЕАЛИЗАЦИИ ВНЕШНЕЙ ЦЕПИ !!!
    km->setControl(keys);
    km->step(t, dt);
}
