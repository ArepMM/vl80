#ifndef		VL80S_H
#define		VL80S_H

#include    <vehicle-api.h>

#include    <km-84.h>
#include    <battery.h>
#include    <shield-215.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class VL80s : public Vehicle
{
public:

    VL80s(QObject *parent = Q_NULLPTR);

    ~VL80s();

    /// Инициализация тормозных приборов
    void initBrakeDevices(double p0, double pBP, double pFL) override;

private:

    /// Чтение дополнительных параметров из конфига
    void loadConfig(QString cfg_path) override;

    // Параметры:
    /// Передаточное число зубчатой передачи тяговых электродвигателей
    double  ip = 4.19;

    /// Имя модуля сцепного устройства
    QString coupling_module_name = "sa3";
    /// Имя конфига сцепного устройства
    QString coupling_config_name = "sa3";

    /// Объём главных резервуаров
    double main_reservoir_volume = 0.9;
    /// Темп утечек из главных резервуаров
    double main_reservoir_leak_flow = 1.0e-6;

    /// Начальное состояние блокировки тормозов
    bool brake_lock_init_state = 0;

    /// Начальное положение комбинированного крана
    int combine_crane_init_pos = 0;

    /// Имя модуля поездного крана
    QString brake_crane_module_name = "krm395";
    /// Имя конфига поездного крана
    QString brake_crane_config_name = "krm395";
    /// Начальное положение поездного крана
    int brake_crane_init_pos = 6;

    /// Имя модуля локомотивного крана
    QString loco_crane_module_name = "kvt254";
    /// Имя конфига локомотивного крана
    QString loco_crane_config_name = "kvt254";
    /// Начальное положение поездного крана
    double loco_crane_init_pos = 1.0;

    /// Имя модуля воздухораспределителя
    QString airdist_module_name = "vr483";
    /// Имя конфига воздухорапределителя
    QString airdist_config_name = "vr483";

    // Оборудование:
    /// Мотор-компрессор
    ACMotorCompressor *motor_compressor = nullptr;

    /// Регулятор давления в ГР
    PressureRegulator *press_reg = nullptr;

    /// Главный резервуар
    Reservoir   *main_reservoir = nullptr;

    /// Концевой кран питательной магистрали спереди
    PneumoAngleCock *anglecock_fl_fwd = nullptr;

    /// Концевой кран питательной магистрали сзади
    PneumoAngleCock *anglecock_fl_bwd = nullptr;

    /// Рукав питательной  магистрали спереди
    PneumoHose      *hose_fl_fwd = nullptr;

    /// Рукав питательной  магистрали сзади
    PneumoHose      *hose_fl_bwd = nullptr;

    /// Блокировочное устройство УБТ усл.№367м
    BrakeLock   *brake_lock = nullptr;

    /// Поездной кран машиниста усл.№395
    BrakeCrane  *brake_crane = nullptr;

    /// Кран впомогательного тормоза усл.№254
    LocoCrane   *loco_crane = nullptr;

    /// Тормозная магистраль
    Reservoir   *brakepipe = nullptr;

    /// Концевой кран тормозной магистрали спереди
    PneumoAngleCock *anglecock_bp_fwd = Q_NULLPTR;

    /// Концевой кран тормозной магистрали сзади
    PneumoAngleCock *anglecock_bp_bwd = Q_NULLPTR;

    /// Рукав тормозной магистрали спереди
    PneumoHose  *hose_bp_fwd = Q_NULLPTR;

    /// Рукав тормозной магистрали сзади
    PneumoHose  *hose_bp_bwd = Q_NULLPTR;

    /// Контроллер машиниста КМ-84
    ControllerKM84 *km = new ControllerKM84;

    /// Щиток 215
    Shield_215 *shield_215 = new Shield_215(S215_INPUTS_NUM, S215_OUTPUTS_NUM);

    /// АКБ
    Battery *battery = new Battery;

    // Инициализация:
    /// Инициализация подсистем секции электровоза
    void initialization() override;

    /// Инициализация питательной магистрали
    void initPneumoSupply(const QString &modules_dir, const QString &custom_cfg_dir);

    /// Инициализация приборов управления тормозами
    void initBrakesControl(const QString &modules_dir, const QString &custom_cfg_dir);

    /// Инициализация тормозного оборудования
    void initBrakesEquipment(const QString &modules_dir, const QString &custom_cfg_dir);

    /// Инициализация подсистемы питания цепей управления
    void initPowerControlCircuit(const QString &modules_dir, const QString &custom_cfg_dir);

    // Симуляция:
    /// Шаг симуляции всех систем электровоза
    void step(double t, double dt) override;

    /// Моделирование питательной магистрали
    void stepPneumoSupply(double t, double dt);

    /// Моделирование приборов управления тормозами
    void stepBrakesControl(double t, double dt);

    /// Моделирование тормозного оборудования
    void stepBrakesEquipment(double t, double dt);

    /// Моделирование подсистемы питания цепей управления
    void stepPowerControlCircuit(double t, double dt);

    /// Отладочный вывод
    void stepDebugPrint(double t, double dt);
};

#endif // VL80S_H
