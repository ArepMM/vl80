#include    "vl80s.h"

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
void VL80s::initBrakesEquipment(const QString &modules_dir, const QString &custom_cfg_dir)
{
    (void) modules_dir;
    (void) custom_cfg_dir;

    // Тормозная магистраль
    double volume_bp = length * 0.0343 * 0.0343 * Physics::PI / 4.0;
    brakepipe = new Reservoir(volume_bp);
    brakepipe->setLeakCoeff(3e-6);

    // Концевые краны тормозной магистрали
    anglecock_bp_fwd = new PneumoAngleCock();
    anglecock_bp_fwd->setKeyCode(KEY_F2);
    anglecock_bp_fwd->read_config("pneumo-anglecock-BP");
    anglecock_bp_fwd->setPipeVolume(volume_bp);

    anglecock_bp_bwd = new PneumoAngleCock();
    anglecock_bp_bwd->setKeyCode(KEY_F3);
    anglecock_bp_bwd->read_config("pneumo-anglecock-BP");
    anglecock_bp_bwd->setPipeVolume(volume_bp);

    // Рукава тормозной магистрали
    hose_bp_fwd = new PneumoHose();
    hose_bp_fwd->setKeyCode(KEY_F1);
    hose_bp_fwd->read_config("pneumo-hose-BP");
    forward_connectors.push_back(hose_bp_fwd);

    hose_bp_bwd = new PneumoHose();
    hose_bp_bwd->setKeyCode(KEY_F4);
    hose_bp_bwd->read_config("pneumo-hose-BP");
    backward_connectors.push_back(hose_bp_bwd);
}
