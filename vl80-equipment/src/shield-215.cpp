#include    <shield-215.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Shield_215::Shield_215(size_t input_wires_num,
                       size_t output_wires_num,
                       QObject *parent)
    : ElectricModule(input_wires_num, output_wires_num, parent)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Shield_215::~Shield_215()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_215::preStep(state_vector_t &Y, double t)
{
    Q_UNUSED(Y)
    Q_UNUSED(t)

    output_wire[N01] = static_cast<double>(circuit_breaker[VA1].getState()) * input_wire[N0];
    output_wire[N02] = static_cast<double>(circuit_breaker[VA2].getState()) * input_wire[N0];
    output_wire[N03] = static_cast<double>(circuit_breaker[VA3].getState()) * input_wire[N0];
    output_wire[N04] = static_cast<double>(circuit_breaker[VA4].getState()) * input_wire[N0];
    output_wire[N05] = static_cast<double>(circuit_breaker[VA5].getState()) * input_wire[N0];

    output_wire[N122] = static_cast<double>(circuit_breaker[VA6].getState()) * input_wire[N119];

    output_wire[E94] = static_cast<double>(circuit_breaker[VA8].getState()) * input_wire[N113];

    output_wire[N09] = static_cast<double>(circuit_breaker[VA9].getState()) * input_wire[N0];
    output_wire[N010] = static_cast<double>(circuit_breaker[VA10].getState()) * input_wire[N0];
    output_wire[N011] = static_cast<double>(circuit_breaker[VA11].getState()) * input_wire[N0];
    output_wire[N012] = static_cast<double>(circuit_breaker[VA12].getState()) * input_wire[N0];
    output_wire[N013] = static_cast<double>(circuit_breaker[VA13].getState()) * input_wire[N0];
    output_wire[N014] = static_cast<double>(circuit_breaker[VA14].getState()) * input_wire[N0];
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_215::ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t)
{
    Q_UNUSED(Y)
    Q_UNUSED(dYdt)
    Q_UNUSED(t)
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_215::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    bool init_state = false;
    cfg.getBool(secName, "InitState", init_state);

    if (init_state)
    {
        for (size_t i = 0; i < circuit_breaker.size(); ++i)
        {
            circuit_breaker[i].set();
        }
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_215::stepKeysControl(double t, double dt)
{

}
