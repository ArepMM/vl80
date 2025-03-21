#include    <shield-223.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Shield_223::Shield_223(size_t input_wires_num,
                       size_t output_wires_num,
                       QObject *parent)
    : ElectricModule(input_wires_num, output_wires_num, parent)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Shield_223::~Shield_223()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_223::preStep(state_vector_t &Y, double t)
{
    Q_UNUSED(Y)
    Q_UNUSED(t)

    output_wire[N88] =
        input_wire[N01] * static_cast<double>(tumbler[TUMBLER_GV_OFF].getState());

    output_wire[E14] =
        input_wire[N01] * static_cast<double>(tumbler[TUMBLER_GV_ON].getState());

    output_wire[E15] =
        input_wire[N01] * static_cast<double>(tumbler[TUMBLER_PANTS].getState());

    output_wire[E16] =
        max(output_wire[E15] * static_cast<double>(tumbler[TUMBLER_PANT_FWD].getState()), input_wire[SME_E16]);

    output_wire[E17] =
        max(output_wire[E15] * static_cast<double>(tumbler[TUMBLER_PANT_BWD].getState()), input_wire[SME_E17]);

    output_wire[E1] =
        input_wire[N02] * static_cast<double>(tumbler[TUMBLER_CTRL_CIRCUIT].getState());

    output_wire[N151] =
        input_wire[N011] * static_cast<double>(tumbler[TUMBLER_SPOT_LIGHT].getState());

    output_wire[N152] =
        output_wire[N151] * static_cast<double>(tumbler[TUMBLER_SPOT_LIGHT_BRIGHT].getState());
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_223::ode_system(const state_vector_t &Y,
                            state_vector_t &dYdt,
                            double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_223::load_config(CfgReader &cfg)
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
void Shield_223::stepKeysControl(double t, double dt)
{
    // Выключение ГВ
    if (getKeyState(KEY_P))
    {
        if (isShift())
        {
            tumbler[TUMBLER_GV_OFF].set();
        }
        else
        {
            tumbler[TUMBLER_GV_OFF].reset();
        }
    }

    // Включение ГВ и возврат защиты реле
    if (getKeyState(KEY_K))
    {
        tumbler[TUMBLER_GV_ON].set();
    }
    else
    {
        tumbler[TUMBLER_GV_ON].reset();
    }

    // Токоприемники
    if (getKeyState(KEY_U))
    {
        if (isShift())
        {
            tumbler[TUMBLER_PANTS].set();
        }
        else
        {
            tumbler[TUMBLER_PANTS].reset();
        }
    }

    // Токоприемник передний
    if (getKeyState(KEY_I))
    {
        if (isShift())
        {
            tumbler[TUMBLER_PANT_FWD].set();
        }
        else
        {
            tumbler[TUMBLER_PANT_FWD].reset();
        }
    }

    // Токоприемник задний
    if (getKeyState(KEY_O))
    {
        if (isShift())
        {
            tumbler[TUMBLER_PANT_BWD].set();
        }
        else
        {
            tumbler[TUMBLER_PANT_BWD].reset();
        }
    }

    // Цепи управления
    if (getKeyState(KEY_J))
    {
        if (isShift())
        {
            tumbler[TUMBLER_CTRL_CIRCUIT].set();
        }
        else
        {
            tumbler[TUMBLER_CTRL_CIRCUIT].reset();
        }
    }
}
