#include    "vl80s.h"
#include    <QDir>

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

    // Воздухораспределитель
    air_dist = loadAirDistributor(modules_dir + QDir::separator() + airdist_module_name);
    air_dist->read_config(airdist_config_name);

    // Запасный резервуар
    supply_reservoir = new Reservoir(supply_reservoir_volume);
    supply_reservoir->setLeakCoeff(supply_reservoir_leak_flow);

    // Разобщительный кран воздухораспределителя и тормозной магистрали
    shutoff_ad_bp = new PneumoShutoffValve();
    shutoff_ad_bp->read_config("pneumo-shutoff-valve-atm", custom_cfg_dir); // Потом перенести конфиг в дефолтные и читать оттуда
    shutoff_ad_bp_init_state ? shutoff_ad_bp->open() : shutoff_ad_bp->close();
    shutoff_ad_bp->setKeyCode(KEY_Period); // Оба разобщительных на одну клавишу

    // Разобщительный кран воздухораспределителя и импульсной магистрали
    shutoff_ad_il = new PneumoShutoffValve();
    shutoff_ad_il->read_config("pneumo-shutoff-valve-atm", custom_cfg_dir); // Потом перенести конфиг в дефолтные и читать оттуда
    shutoff_ad_il_init_state ? shutoff_ad_il->open() : shutoff_ad_il->close();
    shutoff_ad_il->setKeyCode(KEY_Period); // Оба разобщительных на одну клавишу

    // Тормозные рычажные передачи
    brake_mech[TROLLEY_FWD] = new BrakeMech(NUM_AXIS_PER_TROLLEY);
    brake_mech[TROLLEY_FWD]->read_config("brake-mech-fwd", custom_cfg_dir);
    brake_mech[TROLLEY_FWD]->setWheelRadius(rk[0]);
    brake_mech[TROLLEY_FWD]->setEffFricRadius(rk[0]);

    brake_mech[TROLLEY_BWD] = new BrakeMech(NUM_AXIS_PER_TROLLEY);
    brake_mech[TROLLEY_BWD]->read_config("brake-mech-bwd", custom_cfg_dir);
    brake_mech[TROLLEY_BWD]->setWheelRadius(rk[NUM_AXIS_PER_TROLLEY]);
    brake_mech[TROLLEY_BWD]->setEffFricRadius(rk[NUM_AXIS_PER_TROLLEY]);

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
