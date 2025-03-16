#include    <vl80s.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void VL80s::initPowerControlCircuit(const QString &modules_dir,
                                    const QString &custom_cfg_dir)
{
    battery->read_config("battery", custom_cfg_dir);
}
