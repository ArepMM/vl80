#include    <shield-227.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Shield_227::Shield_227(size_t input_wires_num,
                       size_t output_wires_num,
                       QObject *parent)
    : ElectricModule(input_wires_num, output_wires_num, parent)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Shield_227::~Shield_227()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_227::preStep(state_vector_t &Y, double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_227::ode_system(const state_vector_t &Y,
                            state_vector_t &dYdt,
                            double t)
{
    output_wire[N169] =
        input_wire[E18] * static_cast<double>(tumbler[TUMBLER_WITHOUT_PHASE_SPLITTER].getState());

    output_wire[N103] =
        input_wire[N101] * static_cast<double>(tumbler[TUMBLER_PHASE_SPLITTER].getState());

    output_wire[N127] =
        input_wire[N511] * static_cast<double>(tumbler[TUMBLER_FAN1].getState());

    output_wire[N131] =
        input_wire[N513] * static_cast<double>(tumbler[TUMBLER_FAN3].getState());

    output_wire[N121] =
        input_wire[N505] * static_cast<double>(tumbler[TUMBLER_OILPUMP].getState());

    output_wire[N426] =
        input_wire[N010] * static_cast<double>(tumbler[TUMBLER_LOW_OIL_TEMPERATURE].getState());

    output_wire[N67] =
        input_wire[N66] * static_cast<double>(tumbler[TUMBLER_AUX_COMPRESSOR].getState());
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_227::load_config(CfgReader &cfg)
{
    QDomNode secNode = cfg.getFirstSection("Tumbler");

    while (!secNode.isNull())
    {
        int number = 0;
        cfg.getInt(secNode, "Number", number);

        if (number >= tumbler.size())
        {
            break;
        }

        bool state = false;
        cfg.getBool(secNode, "InitState", state);

        if (state)
        {
            tumbler[number].set();
        }
        else
        {
            tumbler[number].reset();
        }

        secNode = cfg.getNextSection();
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_227::stepKeysControl(double t, double dt)
{
    if (getKeyState(KEY_8))
    {
        if (isShift())
        {
            tumbler[TUMBLER_AUX_COMPRESSOR].set();
        }
        else
        {
            tumbler[TUMBLER_AUX_COMPRESSOR].reset();
        }
    }
}
