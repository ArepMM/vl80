#include    "vl80s.h"

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
void VL80s::initPneumoSupply(const QString &modules_dir, const QString &custom_cfg_dir)
{
    (void) modules_dir;
    (void) custom_cfg_dir;

    // Мотор-компрессор
    press_reg = new PressureRegulator();
    press_reg->read_config("pressure-regulator");

    // Мотор-компрессор
    motor_compressor = new ACMotorCompressor();
    motor_compressor->read_config("motor-compressor-ac");

    // Главный резервуар и питательная магистраль
    main_reservoir = new Reservoir(main_reservoir_volume);
    main_reservoir->setLeakCoeff(main_reservoir_leak_flow);
}
