#include    <shield-216.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Shield_216::Shield_216(size_t input_wires_num,
                       size_t output_wires_num,
                       QObject *parent)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Shield_216::~Shield_216()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_216::preStep(state_vector_t &Y, double t)
{
    output_wire[N032] =
        input_wire[N0] * static_cast<double>(azv[VA32].getState());

    output_wire[N033] =
        input_wire[N0] * static_cast<double>(azv[VA33].getState());

    output_wire[N034] =
        input_wire[N0] * static_cast<double>(azv[VA34].getState());

    output_wire[N035] =
        input_wire[N0] * static_cast<double>(azv[VA35].getState());

    output_wire[N036] =
        input_wire[N0] * static_cast<double>(azv[VA36].getState());
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_216::ode_system(const state_vector_t &Y,
                            state_vector_t &dYdt,
                            double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_216::load_config(CfgReader &cfg)
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
            break;
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
void Shield_216::stepKeysControl(double t, double dt)
{

}
