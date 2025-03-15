#include    "vl80s.h"
#include    <QDir>

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
void VL80s::initBrakesControl(const QString &modules_dir, const QString &custom_cfg_dir)
{
    (void) modules_dir;

    // Блокировочное устройство
    brake_lock = new BrakeLock();
    brake_lock->read_config("ubt367m");
    brake_lock->setState(brake_lock_init_state);
    brake_lock->setCombineCranePosition(combine_crane_init_pos);

    // Поездной кран машиниста
    brake_crane = loadBrakeCrane(
                modules_dir + QDir::separator() + brake_crane_module_name);
    brake_crane->read_config(brake_crane_config_name);
    brake_crane->setHandlePosition(brake_crane_init_pos - 1);

    // Кран вспомогательного тормоза
    loco_crane = loadLocoCrane(
                modules_dir + QDir::separator() + loco_crane_module_name);
    loco_crane->read_config(loco_crane_config_name);
    loco_crane->setHandlePosition(loco_crane_init_pos);
}
