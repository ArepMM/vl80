#include    <power-unit.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
PowerUnit::PowerUnit(size_t input_wires_num,
                    size_t output_wires_num,
                    QObject *parent)
    : ElectricModule(input_wires_num, output_wires_num, parent)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
PowerUnit::~PowerUnit()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void PowerUnit::step(double t, double dt)
{
    ElectricModule::step(t, dt);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void PowerUnit::init(const QString &custom_cfg_dir)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void PowerUnit::preStep(state_vector_t &Y, double t)
{
    output_wire[N43] =
        input_wire[E15] * static_cast<double>(S19.getState());

    output_wire[N44] =
        output_wire[N43] * static_cast<double>(S20.getState());
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void PowerUnit::ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void PowerUnit::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    bool S19_state = false;
    cfg.getBool(secName, "S19", S19_state);

    if (S19_state)
    {
        S19.set();
    }
    else
    {
        S19.reset();
    }

    bool S20_state = false;
    cfg.getBool(secName, "S20", S20_state);

    if (S19_state)
    {
        S20.set();
    }
    else
    {
        S20.reset();
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void PowerUnit::stepKeysControl(double t, double dt)
{

}
