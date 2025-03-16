#include    <shield-210.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Shield_210::Shield_210(size_t input_wires_num,
                       size_t output_wires_num,
                       QObject *parent)
    : ElectricModule(input_wires_num, output_wires_num, parent)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Shield_210::~Shield_210()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_210::init(const QString &custom_cfg_dir)
{
    K->read_config("mk-69", custom_cfg_dir);
    K->setInitContactState(K_9_21, true);
    K->setInitContactState(K_31_32, true);
    K->setInitContactState(K_16_17, true);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_210::step(double t, double dt)
{
    ElectricModule::step(t, dt);

    K->step(t, dt);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_210::preStep(state_vector_t &Y, double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_210::ode_system(const state_vector_t &Y,
                            state_vector_t &dYdt,
                            double t)
{
    // Провод Н116 ("+" АКБ)
    bool is_N116_ON = switch_2R.getState();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_210::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    bool switch_2R_state = false;
    cfg.getBool(secName, "Switch2R_state", switch_2R_state);

    if (switch_2R_state)
    {
        switch_2R.set();
    }

    bool switch_3R_state = false;
    cfg.getBool(secName, "Switch3R_state", switch_3R_state);

    if (switch_3R_state)
    {
        switch_3R.set();
    }
}

void Shield_210::stepKeysControl(double t, double dt)
{

}
