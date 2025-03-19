#include	<vl80s.h>
#include    "filesystem.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
VL80s::VL80s(QObject *parent) : Vehicle(parent)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
VL80s::~VL80s()
{

}


//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void VL80s::loadConfig(QString cfg_path)
{
    CfgReader cfg;
    if (cfg.load(cfg_path))
    {
        QString secName = "Settings";

        cfg.getDouble(secName, "ReductorCoeff", ip);
        cfg.getString(secName, "CouplingModule", coupling_module_name);
        cfg.getString(secName, "CouplingConfig", coupling_config_name);
        cfg.getDouble(secName, "MainReservoirVolume", main_reservoir_volume);
        cfg.getDouble(secName, "MainReservoirFlow", main_reservoir_leak_flow);
        cfg.getBool(secName, "BrakeLockState", brake_lock_init_state);
        cfg.getInt(secName, "CombineCranePos", combine_crane_init_pos);
        cfg.getString(secName, "BrakeCraneModule", brake_crane_module_name);
        cfg.getString(secName, "BrakeCraneConfig", brake_crane_config_name);
        cfg.getInt(secName, "BrakeCraneInitPos", brake_crane_init_pos);
        cfg.getString(secName, "LocoCraneModule", loco_crane_module_name);
        cfg.getString(secName, "LocoCraneConfig", loco_crane_config_name);
        cfg.getDouble(secName, "LocoCraneInitPos", loco_crane_init_pos);
        cfg.getString(secName, "AirDistModule", airdist_module_name);
        cfg.getString(secName, "AirDistConfig", airdist_config_name);
        cfg.getDouble(secName, "SupplyReservoirVolume", supply_reservoir_volume);
        cfg.getDouble(secName, "SupplyReservoirFlow", supply_reservoir_leak_flow);
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void VL80s::initialization()
{
    FileSystem &fs = FileSystem::getInstance();
    QString modules_dir(fs.getModulesDir().c_str());
    QString custom_cfg_dir(fs.getVehiclesDir().c_str());
    custom_cfg_dir += fs.separator() + config_dir;

    initCouplings(modules_dir, custom_cfg_dir);

    initPneumoSupply(modules_dir, custom_cfg_dir);

    initBrakesControl(modules_dir, custom_cfg_dir);

    initBrakesEquipment(modules_dir, custom_cfg_dir);

    initPowerControlCircuit(modules_dir, custom_cfg_dir);

    // Контроллер машиниста
    km->init();
    km->read_config("km-84", custom_cfg_dir);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void VL80s::preStep(double t)
{
    preStepCouplings(t);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void VL80s::step(double t, double dt)
{
    stepCouplings(t, dt);

    stepPneumoSupply(t, dt);

    stepBrakesControl(t, dt);

    stepBrakesEquipment(t, dt);

    stepPowerControlCircuit(t, dt);

    // Анимации
    stepSignalsOutput(t, dt);

    // Озвучка
    stepSoundSignalsOutput(t, dt);

    // Отладочная строка
    stepDebugPrint(t, dt);

    km->setControl(keys);
    km->step(t, dt);
}

GET_VEHICLE(VL80s)
