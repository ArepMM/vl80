#ifndef     KM_84_H
#define     KM_84_H

#include    <electric-module.h>
#include    <timer.h>

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
enum KM84_InputWires
{
    KM84_NUM_INPUTS = 5,
    KM84_N1 = 0,
    KM84_N03 = 1,
    KM84_N04 = 2,
    KM84_N05 = 3,
    KM84_N306 = 4
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
enum KM84_OutputWires
{
    KM84_OUTPUTS_NUM = 19,
    KM84_E2 = 0,
    KM84_E3 = 1,
    KM84_E4 = 2,
    KM84_E5 = 3,
    KM84_E6 = 4,
    KM84_N414 = 5,
    KM84_E119 = 6,
    KM84_E56 = 7,
    KM84_E60 = 8,
    KM84_E59 = 9,
    KM84_N302 = 10,
    KM84_N2 = 11,
    KM84_N415 = 12,
    KM84_E115 = 13,

    KM84_E8 = 15,
    KM84_E10 = 16,
    KM84_E11 = 17,
    KM84_E12 = 18
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

    void init();

    float getMainHandlePos() const;

    float getReversHandlePos() const;

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

    /// Направление вращение сельсина-задатчика скорости торможения
    int selsin_dir = 0;

    /// Скорость вращения тормозной рукоятки
    double selsin_omega = 0.0;

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
