#include    <shield-228.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Shield_228::Shield_228(size_t input_wires_num,
                       size_t output_wires_num,
                       QObject *parent)
    : ElectricModule(input_wires_num, output_wires_num, parent)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Shield_228::~Shield_228()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_228::preStep(state_vector_t &Y, double t)
{
    output_wire[N178] =
        input_wire[N014] * static_cast<double>(tumbler[TUMBLER_SVISTOK].getState());

    output_wire[E57] =
        input_wire[N014] * static_cast<double>(tumbler[TUMBLER_TIFON].getState());

    output_wire[E36] =
        input_wire[N014] * static_cast<double>(tumbler[TUMBLER_SAND].getState());
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_228::ode_system(const state_vector_t &Y,
                            state_vector_t &dYdt,
                            double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_228::load_config(CfgReader &cfg)
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
void Shield_228::stepKeysControl(double t, double dt)
{
    if (getKeyState(KEY_Space))
    {
        tumbler[TUMBLER_SVISTOK].set();
    }
    else
    {
        tumbler[TUMBLER_SVISTOK].reset();
    }

    if (getKeyState(KEY_B))
    {
        tumbler[TUMBLER_TIFON].set();
    }
    else
    {
        tumbler[TUMBLER_TIFON].reset();
    }

    if (getKeyState(KEY_Delete))
    {
        tumbler[TUMBLER_SAND].set();
    }
    else
    {
        tumbler[TUMBLER_SAND].reset();
    }
}
