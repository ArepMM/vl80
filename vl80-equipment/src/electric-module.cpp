#include    <electric-module.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
ElectricModule::ElectricModule(size_t input_wires_num,
                               size_t output_wires_num,
                               QObject *parent)
    : Device(parent)
{
    input_wire.resize(input_wires_num);
    std::fill(input_wire.begin(), input_wire.end(), 0.0);

    output_wire.resize(output_wires_num);

    std::fill(output_wire.begin(), output_wire.end(), 0.0);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
ElectricModule::~ElectricModule()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ElectricModule::step(double t, double dt)
{
    Device::step(t, dt);

    if (analogSignal == nullptr)
    {
        return;
    }

    stepSoundsSignals(t, dt);

    stepAnimationsSignals(t, dt);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ElectricModule::preStep(state_vector_t &Y, double t)
{
    Q_UNUSED(Y)
    Q_UNUSED(t)
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ElectricModule::ode_system(const state_vector_t &Y,
                                state_vector_t &dYdt,
                                double t)
{
    Q_UNUSED(Y)
    Q_UNUSED(dYdt)
    Q_UNUSED(t)
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ElectricModule::load_config(CfgReader &cfg)
{
    Q_UNUSED(cfg)
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ElectricModule::stepKeysControl(double t, double dt)
{
    Q_UNUSED(t)
    Q_UNUSED(dt)
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ElectricModule::stepSoundsSignals(double t, double dt)
{
    Q_UNUSED(t)
    Q_UNUSED(dt)
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ElectricModule::stepAnimationsSignals(double t, double dt)
{
    Q_UNUSED(t)
    Q_UNUSED(dt)
}
