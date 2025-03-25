#include    <vl80s.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void VL80s::initSME(const QString &modules_dir, const QString &custom_cfg_dir)
{
    (void) modules_dir;
    (void) custom_cfg_dir;

    // Инициализация связей системы многих единиц (СМЕ)
    sme_fwd = new VL80SME();
    sme_fwd->setKeyCode(KEY_Minus);
    sme_fwd->setCustomConfigDir(config_dir);
    forward_connectors.push_back(sme_fwd);

    sme_bwd = new VL80SME();
    sme_bwd->setKeyCode(KEY_Equals);
    sme_bwd->setCustomConfigDir(config_dir);
    backward_connectors.push_back(sme_bwd);
}
