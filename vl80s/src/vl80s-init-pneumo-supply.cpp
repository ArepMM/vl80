#include    "vl80s.h"

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
void VL80s::initPneumoSupply(const QString &modules_dir, const QString &custom_cfg_dir)
{
    (void) modules_dir;
    (void) custom_cfg_dir;

    main_reservoir = new Reservoir(main_reservoir_volume);
    main_reservoir->setLeakCoeff(main_reservoir_leak_flow);
}
