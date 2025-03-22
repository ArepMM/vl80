#include    <shield-229.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Shield_229::Shield_229(size_t input_wires_num,
                       size_t output_wires_num,
                       QObject *parent)
    : ElectricModule(input_wires_num, output_wires_num, parent)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Shield_229::~Shield_229()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_229::preStep(state_vector_t &Y, double t)
{
    output_wire[E36] =
        input_wire[N014] * static_cast<double>(tumbler[TUMBLER_SAND].getState());
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_229::ode_system(const state_vector_t &Y,
                            state_vector_t &dYdt,
                            double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_229::load_config(CfgReader &cfg)
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
void Shield_229::stepKeysControl(double t, double dt)
{

}
