#include    <shield-226.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Shield_226::Shield_226(size_t input_wires_num,
                       size_t output_wires_num,
                       QObject *parent)
    : ElectricModule(input_wires_num, output_wires_num, parent)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Shield_226::~Shield_226()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_226::preStep(state_vector_t &Y, double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_226::ode_system(const state_vector_t &Y,
                            state_vector_t &dYdt,
                            double t)
{
    output_wire[N104] =
        input_wire[N010] * static_cast<double>(tumbler[TUMBLER_COMPRESSOR].getState());

    output_wire[N128] =
        input_wire[N512] * static_cast<double>(tumbler[TUMBLER_FAN2].getState());

    output_wire[N132] =
        input_wire[N514] * static_cast<double>(tumbler[TUMBLER_FAN4].getState());
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_226::load_config(CfgReader &cfg)
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
void Shield_226::stepKeysControl(double t, double dt)
{

}
