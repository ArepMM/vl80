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
void ControllerKM84::init_main_shaft()
{
    std::fill(main_shaft_state[K_51_52].begin(), main_shaft_state[K_51_52].end(), false);
    main_shaft_state[K_51_52][POS_FP] = true;
    main_shaft_state[K_51_52][POS_RP] = true;
    main_shaft_state[K_51_52][POS_AP] = true;

    std::fill(main_shaft_state[K_53_54].begin(), main_shaft_state[K_53_54].end(), false);
    main_shaft_state[K_53_54][POS_FP] = true;
    main_shaft_state[K_53_54][POS_RP] = true;
    main_shaft_state[K_53_54][POS_AP] = true;

    std::fill(main_shaft_state[K_55_56].begin(), main_shaft_state[K_55_56].end(), false);
    main_shaft_state[K_55_56][POS_AV] = true;
    main_shaft_state[K_55_56][POS_RV] = true;
    main_shaft_state[K_55_56][POS_RP] = true;
    main_shaft_state[K_55_56][POS_AP] = true;

    std::fill(main_shaft_state[K_57_58].begin(), main_shaft_state[K_55_56].end(), false);
    main_shaft_state[K_57_58][POS_AV] = true;
    main_shaft_state[K_57_58][POS_FV] = true;
    main_shaft_state[K_57_58][POS_FP] = true;
    main_shaft_state[K_57_58][POS_AP] = true;

    std::fill(main_shaft_state[K_59_60].begin(), main_shaft_state[K_59_60].end(), true);
    main_shaft_state[K_59_60][POS_BV] = false;
    main_shaft_state[K_59_60][POS_0] = false;

    std::fill(main_shaft_state[K_61_62].begin(), main_shaft_state[K_61_62].end(), true);
    main_shaft_state[K_61_62][POS_BV] = false;

    std::fill(main_shaft_state[K_63_64].begin(), main_shaft_state[K_63_64].end(), true);
    main_shaft_state[K_63_64][POS_BV] = false;
    main_shaft_state[K_63_64][POS_0] = false;

    std::fill(main_shaft_state[K_65_66].begin(), main_shaft_state[K_65_66].end(), false);
    main_shaft_state[K_65_66][POS_0] = true;

    std::fill(main_shaft_state[K_67_68].begin(), main_shaft_state[K_67_68].end(), true);
    main_shaft_state[K_67_68][POS_BV] = false;
    main_shaft_state[K_67_68][POS_0] = false;

    std::fill(main_shaft_state[K_69_70].begin(), main_shaft_state[K_69_70].end(), true);
    main_shaft_state[K_69_70][POS_BV] = false;
    main_shaft_state[K_69_70][POS_0] = false;
}
