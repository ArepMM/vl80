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

    output_wire[N01] = static_cast<double>(azv[VA1].getState()) * input_wire[N0];
    output_wire[N02] = static_cast<double>(azv[VA2].getState()) * input_wire[N0];
    output_wire[N03] = static_cast<double>(azv[VA3].getState()) * input_wire[N0];
    output_wire[N04] = static_cast<double>(azv[VA4].getState()) * input_wire[N0];
    output_wire[N05] = static_cast<double>(azv[VA5].getState()) * input_wire[N0];

    output_wire[N122] = static_cast<double>(azv[VA6].getState()) * input_wire[N119];

    output_wire[E94] = static_cast<double>(azv[VA8].getState()) * input_wire[N113];

    output_wire[N09] = static_cast<double>(azv[VA9].getState()) * input_wire[N0];
    output_wire[N010] = static_cast<double>(azv[VA10].getState()) * input_wire[N0];
    output_wire[N011] = static_cast<double>(azv[VA11].getState()) * input_wire[N0];
    output_wire[N012] = static_cast<double>(azv[VA12].getState()) * input_wire[N0];
    output_wire[N013] = static_cast<double>(azv[VA13].getState()) * input_wire[N0];
    output_wire[N014] = static_cast<double>(azv[VA14].getState()) * input_wire[N0];
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
    QString secName = "AZV";

    QDomNode secNode = cfg.getFirstSection(secName);

    while (!secNode.isNull())
    {
        int number = 0;
        bool state = false;

        cfg.getInt(secNode, "Number", number);

        if (number >= azv.size())
        {
            continue;
        }

        cfg.getBool(secNode, "InitState", state);

        if (state)
        {
            azv[number].set();
        }
        else
        {
            azv[number].reset();
        }

        secNode = cfg.getNextSection();
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_215::stepKeysControl(double t, double dt)
{

}
