#ifndef     KM_84_H
#define     KM_84_H

#include    <device.h>

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
class ControllerKM84 : public Device
{
public:

    ControllerKM84(QObject *parent = Q_NULLPTR);

    ~ControllerKM84();

    void init();

private:

    /// Развертка главного вала (состояние контактов в зависиомсти от положения вала)
    std::array<km84_contact_state_t, KM84_MainShaft::MS_NUM_CONTACTS> main_shaft_state;

    /// Развертка реверсивного вала
    std::array<km84_contact_state_t, KM84_ReversShaft::RS_NUM_CONTACTS> revers_shaft_state;

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;

    void stepKeysControl(double t, double dt) override;

    /// Установка начального состояния контактов
    void set_shaft_contacts_state(km84_contact_state_t &shaft_state, bool state);

    /// Инициализация развертки главного вала
    void init_main_shaft();

    /// инициализация развертки реверсивного вала
    void init_revers_shaft();
};

#endif
