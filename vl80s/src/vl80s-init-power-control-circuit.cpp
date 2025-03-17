#include    <vl80s.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void VL80s::initPowerControlCircuit(const QString &modules_dir,
                                    const QString &custom_cfg_dir)
{
    battery->read_config("battery", custom_cfg_dir);

    shield_215->read_config("shield-215", custom_cfg_dir);

    shield_210->read_config("shield-210", custom_cfg_dir);
    shield_210->init(custom_cfg_dir);
}
