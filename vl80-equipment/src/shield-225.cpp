#include    <shield-225.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Shield_225::Shield_225(size_t input_wires_num,
                       size_t output_wires_num,
                       QObject *parent)
    : ElectricModule(input_wires_num, output_wires_num, parent)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Shield_225::~Shield_225()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_225::preStep(state_vector_t &Y, double t)
{
    output_wire[N153] =
        input_wire[N012] * static_cast<double>(tumbler[TUMBLER_TAILLIGHT_RIGHT].getState());

    output_wire[N154] =
        input_wire[N012] * static_cast<double>(tumbler[TUMBLER_TAILLIGHT_LEFT].getState());

    output_wire[N155] =
        input_wire[N013] * static_cast<double>(tumbler[TUMBLER_GAUGES_LIGHT].getState());

    output_wire[N453] =
        input_wire[N033] * static_cast<double>(tumbler[TUMBLER_BOGIE_LIGHT].getState());

    output_wire[N163] =
        input_wire[N013] * static_cast<double>(tumbler[TUMBLER_CAB_LIGHT_HIGH].getState());

    output_wire[N164] =
        input_wire[N013] * static_cast<double>(tumbler[TUMBLER_CAB_LIGHT_LOW].getState());

    output_wire[N160] =
        input_wire[N013] * static_cast<double>(tumbler[TUMBLER_CAB_HEAT_2].getState());

    output_wire[N161] =
        input_wire[N013] * static_cast<double>(tumbler[TUMBLER_CAB_HEAT_3].getState());

    output_wire[N178] =
        input_wire[N014] * static_cast<double>(tumbler[TUMBLER_SVISTOK].getState());

    output_wire[E57] =
        input_wire[N014] * static_cast<double>(tumbler[TUMBLER_SVISTOK].getState());

    output_wire[N139] =
        input_wire[N013] * static_cast<double>(tumbler[TUMBLER_DOCS_LIGHT1].getState());

    output_wire[N159] =
        input_wire[N013] * static_cast<double>(tumbler[TUMBLER_DOCS_LIGHT2].getState());

    output_wire[N145] =
        input_wire[N013] * static_cast<double>(tumbler[TUMBLER_GREEN_LIGHT].getState());
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_225::ode_system(const state_vector_t &Y,
                            state_vector_t &dYdt,
                            double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_225::load_config(CfgReader &cfg)
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
void Shield_225::stepKeysControl(double t, double dt)
{

}
