#include    <vl80s.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void VL80s::initPowerControlCircuit(const QString &modules_dir,
                                    const QString &custom_cfg_dir)
{
    battery->read_config("battery", custom_cfg_dir);

    shield_215->read_config("shield-215", custom_cfg_dir);

    shield_216->read_config("shield-216", custom_cfg_dir);

    shield_210->read_config("shield-210", custom_cfg_dir);
    shield_210->init(custom_cfg_dir);

    shield_223->read_config("shield-223", custom_cfg_dir);

    shield_224->read_config("shield-224", custom_cfg_dir);

    shield_225->read_config("shield-225", custom_cfg_dir);

    shield_226->read_config("shield-226", custom_cfg_dir);

    shield_227->read_config("shield-227", custom_cfg_dir);

    shield_228->read_config("shield-228", custom_cfg_dir);

    shield_229->read_config("shield-229", custom_cfg_dir);

    // Контроллер машиниста
    km->init(custom_cfg_dir);
    km->read_config("km-84", custom_cfg_dir);
}
