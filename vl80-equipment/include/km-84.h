#ifndef     KM_84_H
#define     KM_84_H

#include    <device.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
enum KM84_Position
{
    NUM_POS = 7,
    POS_BV = 0,
    POS_ZERO = 1,
    POS_AV = 2,
    POS_RV = 3,
    POS_FV = 4,
    POS_FP = 5,
    POS_RP = 5,
    POS_AP = 6
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
using km84_contact_state_t = std::array<bool, KM84_Position::NUM_POS>;

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
enum KM84_MainShaft
{
    NUM_CONTACTS = 10,
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
class ControllerKM84 : public Device
{
public:

    ControllerKM84(QObject *parent = Q_NULLPTR);

    ~ControllerKM84();

private:

    /// Развертка главного вала (состояние контактов в зависиомсти от положения вала)
    std::array<km84_contact_state_t, KM84_MainShaft::NUM_CONTACTS> main_shaft_state;

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;

    void stepKeysControl(double t, double dt) override;

    /// Инициализация развертки главного вала
    void init_main_shaft();
};

#endif
