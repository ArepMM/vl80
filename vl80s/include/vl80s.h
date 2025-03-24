#ifndef		VL80S_H
#define		VL80S_H

#include    <vehicle-api.h>

// Потом перенести в движок и в vehicle-api.h
#include    <pneumo-shutoff-valve.h>

#include    <km-84.h>
#include    <battery.h>
#include    <shield-210.h>
#include    <shield-215.h>
#include    <shield-216.h>
#include    <shield-223.h>
#include    <shield-224.h>
#include    <shield-225.h>
#include    <shield-226.h>
#include    <shield-227.h>
#include    <shield-228.h>
#include    <shield-229.h>
#include    <panel-1.h>
#include    <panel-2.h>
#include    <panel-3.h>
#include    <panel-4.h>
#include    <panel-5.h>
#include    <panel-6.h>
#include    <panel-7.h>
#include    <dc-motor.h>
#include    <compressor.h>

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
    bool brake_lock_init_state = false;

    /// Начальное положение комбинированного крана
    int combine_crane_init_pos = 0;

    /// Положение разобщительного крана воздухораспределителя и тормозной магистрали КН8
    bool shutoff_ad_bp_init_state = false;
    /// Положение разобщительного крана воздухораспределителя и импульсной магистрали КН20
    bool shutoff_ad_il_init_state = false;

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

    /// Объём запасного резервуара
    double supply_reservoir_volume = 0.055;
    /// Темп утечек из запасного резервуара
    double supply_reservoir_leak_flow = 1.0e-6;

    // Оборудование:
    /// Сцепка спереди
    Coupling *coupling_fwd = nullptr;
    /// Сцепка сзади
    Coupling *coupling_bwd = nullptr;

    /// Расцепной рычаг спереди
    OperatingRod *oper_rod_fwd = nullptr;
    /// Расцепной рычаг сзади
    OperatingRod *oper_rod_bwd = nullptr;

    /// Мотор-компрессор КМ1
    ACMotorCompressor *motor_compressor = nullptr;

    /// Регулятор давления в главном резервуаре РГД
    PressureRegulator *press_reg = nullptr;

    /// Главный резервуар РС1,РС2,РС3
    Reservoir   *main_reservoir = nullptr;

    /// Концевой кран питательной магистрали спереди КНК1
    PneumoAngleCock *anglecock_fl_fwd = nullptr;

    /// Концевой кран питательной магистрали сзади КН47
    PneumoAngleCock *anglecock_fl_bwd = nullptr;

    /// Рукав питательной  магистрали спереди РУ1
    PneumoHose      *hose_fl_fwd = nullptr;

    /// Рукав питательной  магистрали сзади РУ7
    PneumoHose      *hose_fl_bwd = nullptr;

    /// Блокировочное устройство УБТ усл.№367м
    BrakeLock   *brake_lock = nullptr;

    /// Поездной кран машиниста усл.№395
    BrakeCrane  *brake_crane = nullptr;

    /// Кран впомогательного тормоза усл.№254
    LocoCrane   *loco_crane = nullptr;

    /// Тормозная магистраль
    Reservoir   *brakepipe = nullptr;

    /// Концевой кран тормозной магистрали спереди КНК2
    PneumoAngleCock *anglecock_bp_fwd = nullptr;

    /// Концевой кран тормозной магистрали сзади КНК3
    PneumoAngleCock *anglecock_bp_bwd = nullptr;

    /// Рукав тормозной магистрали спереди РУ2
    PneumoHose  *hose_bp_fwd = nullptr;

    /// Рукав тормозной магистрали сзади РУ3
    PneumoHose  *hose_bp_bwd = nullptr;

    /// Разобщительный кран воздухораспределителя и тормозной магистрали КН8
    PneumoShutoffValve *shutoff_ad_bp = nullptr;

    /// Разобщительный кран воздухораспределителя и импульсной магистрали КН20
    PneumoShutoffValve *shutoff_ad_il = nullptr;

    /// Воздухораспределитель ВР
    AirDistributor  *air_dist = nullptr;

    /// Запасный резервуар РС4
    Reservoir   *supply_reservoir = nullptr;

    /// Импульсная магистраль
    Reservoir   *impulse_line = nullptr;

    /// Концевой кран импульсной магистрали сзади КН48
    PneumoAngleCock  *anglecock_il_bwd = nullptr;

    /// Рукав  импульсной магистрали сзади РУ5
    PneumoHose  *hose_il_bwd = nullptr;

    /// Магистраль тормозных цилиндров (модуль-пневмотройник для потоков в ТЦ)
    PneumoSplitter   *bc_line = nullptr;

    /// Концевой кран магистрали тормозных цилиндров спереди КН50
    PneumoAngleCock  *anglecock_bc_fwd = nullptr;

    /// Концевой кран магистрали тормозных цилиндров сзади КН51
    PneumoAngleCock  *anglecock_bc_bwd = nullptr;

    /// Рукав магистрали тормозных цилиндров спереди РУ4
    PneumoHose  *hose_bc_fwd = nullptr;

    /// Рукав магистрали тормозных цилиндров сзади РУ6
    PneumoHose  *hose_bc_bwd = nullptr;

    /// Повторительное реле давления РД для ТЦ задней тележки усл.№304
    PneumoRelay *bc_pressure_relay = nullptr;

    enum
    {
        NUM_TROLLEYS = 2,
        NUM_AXIS_PER_TROLLEY = 2,
        TROLLEY_FWD = 0,
        TROLLEY_BWD = 1
    };

    /// Тормозные механизмы тележек
    std::array<BrakeMech *, NUM_TROLLEYS> brake_mech;

    /// АКБ
    Battery *battery = new Battery;

    /// Контроллер машиниста КМ-84
    ControllerKM84 *km = new ControllerKM84(ControllerKM84::INPUTS_NUM,
                                            ControllerKM84::OUTPUTS_NUM);

    /// Распеределительный щит 210
    Shield_210 *shield_210 = new Shield_210(Shield_210::INPUTS_NUM,
                                            Shield_210::OUTPUT_NUM);

    /// Щиток 215
    Shield_215 *shield_215 = new Shield_215(Shield_215::INPUTS_NUM,
                                            Shield_215::OUTPUTS_NUM);

    /// Щиток 216
    Shield_216 *shield_216 = new Shield_216(Shield_216::INPUTS_NUM,
                                            Shield_216::OUTPUTS_NUM);

    /// Щиток 223
    Shield_223 *shield_223 = new Shield_223(Shield_223::INPUTS_NUM,
                                            Shield_223::OUTPUTS_NUM);

    /// Щиток 224
    Shield_224 *shield_224 = new Shield_224(Shield_224::INPUTS_NUM,
                                            Shield_224::OUTPUTS_NUM);

    /// Щиток 225
    Shield_225 *shield_225 = new Shield_225(Shield_225::INPUTS_NUM,
                                            Shield_225::OUTPUTS_NUM);

    /// Щиток 226
    Shield_226 *shield_226 = new Shield_226(Shield_226::INPUTS_NUM,
                                            Shield_226::OUTPUTS_NUM);

    /// Щиток 227
    Shield_227 *shield_227 = new Shield_227(Shield_227::INPUTS_NUM,
                                            Shield_227::OUTPUTS_NUM);

    /// Щиток 228
    Shield_228 *shield_228 = new Shield_228(Shield_228::INPUTS_NUM,
                                            Shield_228::OUTPUTS_NUM);

    /// Щиток 229
    Shield_229 *shield_229 = new Shield_229(Shield_229::INPUTS_NUM,
                                            Shield_229::OUTPUTS_NUM);

    /// Панель 1
    Panel_1 *panel_1 = new Panel_1(Panel_1::INPUTS_NUM, Panel_1::OUTPUTS_NUM);

    /// Панель 2
    Panel_2 *panel_2 = new Panel_2(Panel_2::INPUTS_NUM, Panel_2::OUTPUTS_NUM);

    /// Панель 3
    Panel_3 *panel_3 = new Panel_3(Panel_3::INPUTS_NUM, Panel_3::OUTPUTS_NUM);

    /// Панель 4
    Panel_4 *panel_4 = new Panel_4(Panel_4::INPUTS_NUM, Panel_4::OUTPUTS_NUM);

    /// Панель 5
    Panel_5 *panel_5 = new Panel_5(Panel_5::INPUTS_NUM, Panel_5::OUTPUTS_NUM);

    /// Панель 6
    Panel_6 *panel_6 = new Panel_6(Panel_6::INPUTS_NUM, Panel_6::OUTPUTS_NUM);

    /// Панель 7
    Panel_7 *panel_7 = new Panel_7(Panel_7::INPUTS_NUM, Panel_7::OUTPUTS_NUM);

    /// Двигатель вспомогательного компрессора
    DCMotor *aux_compr_motor = new DCMotor;

    /// Вспомогательный компрессор
    Compressor *aux_compr = new Compressor;

    // Инициализация:
    /// Инициализация подсистем секции электровоза
    void initialization() override;

    /// Инициализация сцепных устройств
    void initCouplings(const QString &modules_dir, const QString &custom_cfg_dir);

    /// Инициализация питательной магистрали
    void initPneumoSupply(const QString &modules_dir, const QString &custom_cfg_dir);

    /// Инициализация приборов управления тормозами
    void initBrakesControl(const QString &modules_dir, const QString &custom_cfg_dir);

    /// Инициализация тормозного оборудования
    void initBrakesEquipment(const QString &modules_dir, const QString &custom_cfg_dir);

    /// Инициализация подсистемы питания цепей управления
    void initPowerControlCircuit(const QString &modules_dir, const QString &custom_cfg_dir);

    // Симуляция:
    /// Предварительные расчёты перед симуляцией
    void preStep(double t) override;

    /// Предварительный расчёт координат сцепных устройств
    void preStepCouplings(double t);

    /// Шаг симуляции всех систем электровоза
    void step(double t, double dt) override;

    /// Моделирование сцепных устройств
    void stepCouplings(double t, double dt);

    /// Моделирование питательной магистрали
    void stepPneumoSupply(double t, double dt);

    /// Моделирование приборов управления тормозами
    void stepBrakesControl(double t, double dt);

    /// Моделирование тормозного оборудования
    void stepBrakesEquipment(double t, double dt);

    /// Моделирование подсистемы питания цепей управления
    void stepPowerControlCircuit(double t, double dt);

    /// Вывод сигналов анимаций
    void stepSignalsOutput(double t, double dt);

    /// Вывод сигналов озвучки
    void stepSoundSignalsOutput(double t, double dt);

    /// Отладочный вывод
    void stepDebugPrint(double t, double dt);
};

#endif // VL80S_H
