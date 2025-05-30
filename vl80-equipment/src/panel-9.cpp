#include    <panel-9.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Panel_9::Panel_9(size_t input_wires_num,
                 size_t output_wires_num,
                 QObject *parent)
    : ElectricModule(input_wires_num, output_wires_num, parent)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Panel_9::~Panel_9()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Panel_9::step(double t, double dt)
{
    ElectricModule::step(t, dt);

    K248->setVoltage(input_wire[E37]);
    K248->step(t, dt);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Panel_9::init(const QString &custom_cfg_dir)
{
    K248->read_config("mk-69", custom_cfg_dir);
    K248->setInitContactState(K248_E16_N125, false);
    K248->setInitContactState(K248_E13_N68, false);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Panel_9::preStep(state_vector_t &Y, double t)
{
    output_wire[N125] =
        input_wire[E16] * static_cast<double>(K248->getContactState(K248_E16_N125));

    output_wire[N68] =
        input_wire[E13] * static_cast<double>(K248->getContactState(K248_E13_N68));

    // Ток, потребляемый панелью
    Icc = K248->getCurrent();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Panel_9::ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Panel_9::load_config(CfgReader &cfg)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Panel_9::stepKeysControl(double t, double dt)
{

}
