#include    <km-84.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
ControllerKM84::ControllerKM84(QObject *parent) : Device(parent)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
ControllerKM84::~ControllerKM84()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ControllerKM84::init()
{
    // Инициализируем развертку главного вала
    init_main_shaft();

    // Инициализируем развертку реверсивного вала
    init_revers_shaft();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ControllerKM84::preStep(state_vector_t &Y, double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ControllerKM84::ode_system(const state_vector_t &Y,
                                state_vector_t &dYdt,
                                double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ControllerKM84::load_config(CfgReader &cfg)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ControllerKM84::stepKeysControl(double t, double dt)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ControllerKM84::set_shaft_contacts_state(km84_contact_state_t &shaft_state,
                                             bool state)
{
    std::fill(shaft_state.begin(), shaft_state.end(), state);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ControllerKM84::init_main_shaft()
{
    for (size_t i = 0; i < main_shaft_state.size(); ++i)
    {
        main_shaft_state[i].resize(KM84_Position::NUM_POS);
    }

    set_shaft_contacts_state(main_shaft_state[K_51_52], false);
    main_shaft_state[K_51_52][POS_FP] = true;
    main_shaft_state[K_51_52][POS_RP] = true;
    main_shaft_state[K_51_52][POS_AP] = true;

    set_shaft_contacts_state(main_shaft_state[K_53_54], false);
    main_shaft_state[K_53_54][POS_FP] = true;
    main_shaft_state[K_53_54][POS_RP] = true;
    main_shaft_state[K_53_54][POS_AP] = true;

    set_shaft_contacts_state(main_shaft_state[K_55_56], false);
    main_shaft_state[K_55_56][POS_AV] = true;
    main_shaft_state[K_55_56][POS_RV] = true;
    main_shaft_state[K_55_56][POS_RP] = true;
    main_shaft_state[K_55_56][POS_AP] = true;

    set_shaft_contacts_state(main_shaft_state[K_57_58], false);
    main_shaft_state[K_57_58][POS_AV] = true;
    main_shaft_state[K_57_58][POS_FV] = true;
    main_shaft_state[K_57_58][POS_FP] = true;
    main_shaft_state[K_57_58][POS_AP] = true;

    set_shaft_contacts_state(main_shaft_state[K_59_60], true);
    main_shaft_state[K_59_60][POS_BV] = false;
    main_shaft_state[K_59_60][POS_0] = false;

    set_shaft_contacts_state(main_shaft_state[K_61_62], true);
    main_shaft_state[K_61_62][POS_BV] = false;

    set_shaft_contacts_state(main_shaft_state[K_63_64], true);
    main_shaft_state[K_63_64][POS_BV] = false;
    main_shaft_state[K_63_64][POS_0] = false;

    set_shaft_contacts_state(main_shaft_state[K_65_66], false);
    main_shaft_state[K_65_66][POS_0] = true;

    set_shaft_contacts_state(main_shaft_state[K_67_68], true);
    main_shaft_state[K_67_68][POS_BV] = false;
    main_shaft_state[K_67_68][POS_0] = false;

    set_shaft_contacts_state(main_shaft_state[K_69_70], true);
    main_shaft_state[K_69_70][POS_BV] = false;
    main_shaft_state[K_69_70][POS_0] = false;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ControllerKM84::init_revers_shaft()
{
    for (size_t i = 0; i < revers_shaft_state.size(); ++i)
    {
        revers_shaft_state[i].resize(REVERS_POS_NUM);
    }

    set_shaft_contacts_state(revers_shaft_state[K_1_2], false);
    revers_shaft_state[K_1_2][REVERS_POS_OP1] = true;
    revers_shaft_state[K_1_2][REVERS_POS_OP2] = true;
    revers_shaft_state[K_1_2][REVERS_POS_OP3] = true;

    set_shaft_contacts_state(revers_shaft_state[K_3_4], false);
    revers_shaft_state[K_3_4][REVERS_POS_OP2] = true;
    revers_shaft_state[K_3_4][REVERS_POS_OP3] = true;

    set_shaft_contacts_state(revers_shaft_state[K_5_6], false);
    revers_shaft_state[K_5_6][REVERS_POS_OP3] = true;

    set_shaft_contacts_state(revers_shaft_state[K_7_8], false);

    set_shaft_contacts_state(revers_shaft_state[K_9_10], false);
    revers_shaft_state[K_9_10][REVERS_POS_BACKWARD] = true;

    set_shaft_contacts_state(revers_shaft_state[K_11_12], true);
    revers_shaft_state[K_11_12][REVERS_POS_BACKWARD] = false;
    revers_shaft_state[K_11_12][REVERS_POS_0] = false;

    set_shaft_contacts_state(revers_shaft_state[K_13_14], true);
    revers_shaft_state[K_13_14][REVERS_POS_0] = false;

    set_shaft_contacts_state(revers_shaft_state[K_15_16], true);
    revers_shaft_state[K_15_16][REVERS_POS_0] = false;
}
