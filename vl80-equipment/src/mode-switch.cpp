#include    <mode-switch.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
ModeSwitch::ModeSwitch(size_t input_wires_num,
                       size_t output_wires_num,
                       QObject *parent)
    : ElectricModule(input_wires_num, output_wires_num, parent)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
ModeSwitch::~ModeSwitch()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ModeSwitch::step(double t, double dt)
{
    ElectricModule::step(t, dt);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ModeSwitch::init(const QString &custom_cfg_dir)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ModeSwitch::preStep(state_vector_t &Y, double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ModeSwitch::ode_system(const state_vector_t &Y,
                            state_vector_t &dYdt,
                            double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ModeSwitch::load_config(CfgReader &cfg)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ModeSwitch::stepKeysControl(double t, double dt)
{

}
