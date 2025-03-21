#ifndef     KM_84_H
#define     KM_84_H

#include    <electric-module.h>
#include    <timer.h>
#include    <selsyn.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
enum KM84_Position
{
    NUM_POS = 8,
    POS_BV = 0,
    POS_0 = 1,
    POS_AV = 2,
    POS_RV = 3,
    POS_FV = 4,
    POS_FP = 5,
    POS_RP = 6,
    POS_AP = 7
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
using km84_contact_state_t = std::vector<bool>;

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
enum KM84_MainShaft
{
    MS_NUM_CONTACTS = 10,
    K_51_52 = 0,
    K_53_54 = 1,
    K_55_56 = 2,
    K_57_58 = 3,
    K_59_60 = 4,
    K_61_62 = 5,
    K_63_64 = 6,
    K_65_66 = 7,
    K_67_68 = 8,
    K_69_70 = 9,
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
enum KM84_ReversShaft
{
    RS_NUM_CONTACTS = 8,
    K_1_2 = 0,
    K_3_4 = 1,
    K_5_6 = 2,
    K_7_8 = 3,
    K_9_10 = 4,
    K_11_12 = 5,
    K_13_14 = 6,
    K_15_16 = 7
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
enum KM84_ResersPos
{
    REVERS_POS_NUM = 6,
    REVERS_POS_BACKWARD = 0,
    REVERS_POS_0 = 1,
    REVERS_POS_FORWARD = 2,
    REVERS_POS_OP1 = 3,
    REVERS_POS_OP2 = 4,
    REVERS_POS_OP3 = 5
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
enum KM84_BrakePos
{
    BRAKE_NUM_POS = 4,
    BRAKE_POS_0 = 0,
    BRAKE_POS_P = 1,
    BRAKE_POS_PT = 2,
    BRAKE_POS_T = 3
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
enum KM84_BrakeShaft
{
    BS_NUM_CONTACTS = 5,
    K_31_32 = 0,
    K_33_34 = 1,
    K_35_36 = 2,
    K_37_38 = 3,
    K_39_40 = 4
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class ControllerKM84 : public ElectricModule
{
public:

    ControllerKM84(size_t input_wires_num = 1,
                   size_t output_wires_num = 1,
                   QObject *parent = Q_NULLPTR);

    ~ControllerKM84();

    void init(const QString &custom_cfg_dir);

    /// Положение главной рукоятки
    float getMainHandlePos() const;

    /// Положение реверсивной рукоятки
    float getReversHandlePos() const;

    /// Положение тормозной рукоятки
    float getBrakeHandlePos() const;

    enum KM84_InputWires
    {
        INPUTS_NUM = 6,
        N1 = 0,
        N03 = 1,
        N04 = 2,
        N05 = 3,
        N306 = 4,
        N88 = 5
    };

    enum KM84_OutputWires
    {
        OUTPUTS_NUM = 20,
        E2 = 0,
        E3 = 1,
        E4 = 2,
        E5 = 3,
        E6 = 4,
        N414 = 5,
        E119 = 6,
        E56 = 7,
        E60 = 8,
        E59 = 9,
        N302 = 10,
        N2 = 11,
        N415 = 12,
        E115 = 13,

        E8 = 15,
        E10 = 16,
        E11 = 17,
        E12 = 18,
        E13 = 19
    };

    enum
    {
        NUM_SOUNDS = 3,
        REVERS_CHANGE_POS_SOUND = 0,
        MAIN_CHANGE_POS_SOUND = 1,
        BRAKE_CHANGE_POS_SOUND = 2
    };

    sound_state_t getSoundState(size_t idx = REVERS_CHANGE_POS_SOUND) const override;

    float getSoundSignal(size_t idx = REVERS_CHANGE_POS_SOUND) const override;

    QString getBrakePosName() const
    {
        return brake_pos_name[brake_pos];
    }

    QString getReversPosName() const
    {
        return revers_pos_name[revers_pos];
    }

    QString getMainPosName() const
    {
        return main_pos_name[main_pos];
    }

    double getBrakeShaftAngle() const
    {
        return brake_shaft_angle;
    }

    void step(double t, double dt) override;

private:

    /// Развертка главного вала (состояние контактов в зависиомсти от положения вала)
    std::array<km84_contact_state_t, KM84_MainShaft::MS_NUM_CONTACTS> main_shaft_state;

    /// Развертка реверсивного вала
    std::array<km84_contact_state_t, KM84_ReversShaft::RS_NUM_CONTACTS> revers_shaft_state;

    /// Развертка тормозного вала
    std::array<km84_contact_state_t, KM84_BrakeShaft::BS_NUM_CONTACTS> brake_shaft_state;

    /// Положение главного вала
    int main_pos = KM84_Position::POS_0;

    /// Положение реверсивного вала
    int revers_pos = KM84_ResersPos::REVERS_POS_0;

    /// Положение тормозного вала
    int brake_pos = KM84_BrakePos::BRAKE_POS_0;

    /// Таймаут переключения позиций при зажатых клавишах
    double switch_timeout = 0.3;

    /// Таймеры управления главным валом
    Timer *main_shaft_timer = Q_NULLPTR;

    /// Таймер управления реверсивным валом
    Timer *revers_shaft_timer = Q_NULLPTR;

    /// Таймер управления тормозным валом
    Timer *brake_shaft_timer = Q_NULLPTR;

    /// Направление вращения главного вала
    int main_shaft_dir = 1;

    /// Направление вращения реверсивного вала
    int revers_shaft_dir = 1;

    /// Направление вращения тормозного вала
    int brake_shaft_dir = 1;

    /// Угол поворота тормозного вала
    double brake_shaft_angle = 0.0;

    /// Скорость вращения тормозного вала
    double brake_shaft_omega = 0.0;

    /// Максимальный угол поворота тормозного вала
    double brake_shaft_angle_max = 270.0;

    /// Сельсин-задатчик скорости торможения
    Selsyn *selsyn = new Selsyn;

    /// Углы поворота тормозного вала на дискрретных позициях
    std::array<double, BRAKE_NUM_POS> bs_angles = {0, 20.0, 40.0, 60.0};

    /// Названия позиций главной рукоятки
    std::vector<QString> main_pos_name = {"БВ", "0", "АВ", "РВ", "ФВ", "ФП", "РП", "АП"};

    /// Названия позиций реверсивной рукоятки
    std::vector<QString> revers_pos_name = {"ППН", "0", "ППВ", "ОП1", "ОП2", "ОП3"};

    /// Назавания положений позиций тормозной рукоятки
    std::vector<QString> brake_pos_name = {"0", "П", "ПТ", "Т"};

    /// Счетчик и состояние звуков
    std::array<sound_state_t, NUM_SOUNDS> sounds;

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                            state_vector_t &dYdt,
                            double t) override;

    void load_config(CfgReader &cfg) override;

    void stepKeysControl(double t, double dt) override;

    /// Установка начального состояния контактов вала
    void set_shaft_contacts_state(km84_contact_state_t &shaft_state, bool state);

    /// Инициализация развертки главного вала
    void init_main_shaft();

    /// Инициализация развертки реверсивного вала
    void init_revers_shaft();

    /// Инициализация развертки тормозного вала
    void init_brake_shaft();

private slots:

    void slotMainShaftUpdate();

    void slotReversShaftUpdate();

    void slotBrakeShaftUpdate();
};

#endif
