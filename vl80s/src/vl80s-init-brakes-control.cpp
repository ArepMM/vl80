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

    double volume = length * 0.0343 * 0.0343 * Physics::PI / 4.0;
    // Импульсная магистраль
    impulse_line = new Reservoir(volume);
    // Магистраль тормозных цилиндров
    bc_line = new PneumoSplitter();
    bc_line->read_config("bc-splitter", custom_cfg_dir);

    // Повторительное реле давления в ТЦ задней тележки
    bc_pressure_relay = new PneumoRelay();
    bc_pressure_relay->read_config("rd304");

    // TODO // отдельный конфиг и отдельное управление
    // Концевой кран импульсной магистрали сзади
    anglecock_il_bwd = new PneumoAngleCock();
    //anglecock_il_bwd->setKeyCode(KEY_F11);
    anglecock_il_bwd->read_config("pneumo-anglecock-BC");

    // TODO // отдельный конфиг и отдельное управление
    // Рукав импульсной магистрали сзади
    hose_il_bwd = new PneumoHose();
    //hose_il_bwd->setKeyCode(KEY_F12);
    hose_il_bwd->read_config("pneumo-hose-BC");
    //backward_connectors.push_back(hose_il_bwd);

    // Концевые краны магистрали тормозных цилиндров
    anglecock_bc_fwd = new PneumoAngleCock();
    anglecock_bc_fwd->setKeyCode(KEY_F10);
    anglecock_bc_fwd->read_config("pneumo-anglecock-BC");

    anglecock_bc_bwd = new PneumoAngleCock();
    anglecock_bc_bwd->setKeyCode(KEY_F11);
    anglecock_bc_bwd->read_config("pneumo-anglecock-BC");

    // Рукава магистрали тормозных цилиндров
    hose_bc_fwd = new PneumoHose();
    hose_bc_fwd->setKeyCode(KEY_F9);
    hose_bc_fwd->read_config("pneumo-hose-BC");
    forward_connectors.push_back(hose_bc_fwd);

    hose_bc_bwd = new PneumoHose();
    hose_bc_bwd->setKeyCode(KEY_F12);
    hose_bc_bwd->read_config("pneumo-hose-BC");
    backward_connectors.push_back(hose_bc_bwd);
}
