#include    <shield-224.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Shield_224::Shield_224(size_t input_wires_num,
                       size_t output_wires_num,
                       QObject *parent)
    : ElectricModule(input_wires_num, output_wires_num, parent)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Shield_224::~Shield_224()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_224::preStep(state_vector_t &Y, double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_224::ode_system(const state_vector_t &Y,
                            state_vector_t &dYdt,
                            double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_224::load_config(CfgReader &cfg)
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
void Shield_224::stepKeysControl(double t, double dt)
{
    // Вспомогательные машины
    if (getKeyState(KEY_T))
    {
        if (isShift())
        {
            tumbler[TUMBLER_AUX_MASHINES].set();
        }
        else
        {
            tumbler[TUMBLER_AUX_MASHINES].reset();
        }
    }

    // Фазоращепитель (НЕ ФИКСИРУЕТСЯ!!! С ВОЗВРАТОМ!!!)
    if (getKeyState(KEY_F) && isShift())
    {
        tumbler[TUMBLER_PHASE_SPLITTER].set();
    }
    else
    {
        tumbler[TUMBLER_PHASE_SPLITTER].reset();
    }

    // Компрессоры
    if (getKeyState(KEY_C))
    {
        if (isShift())
        {
            tumbler[TUMBLER_COMPRESSORS].set();
        }
        else
        {
            tumbler[TUMBLER_COMPRESSORS].reset();
        }
    }

    // Вентилятор 1 (НЕ ФИКСИРУЕТСЯ!!! С ВОЗВРАТОМ!!!)
    if (getKeyState(KEY_1) && isShift())
    {
        tumbler[TUMBLER_FAN1].set();
    }
    else
    {
        tumbler[TUMBLER_FAN1].reset();
    }

    // Вентилятор 2 (НЕ ФИКСИРУЕТСЯ!!! С ВОЗВРАТОМ!!!)
    if (getKeyState(KEY_2) && isShift())
    {
        tumbler[TUMBLER_FAN2].set();
    }
    else
    {
        tumbler[TUMBLER_FAN2].reset();
    }

    // Вентилятор 3 (НЕ ФИКСИРУЕТСЯ!!! С ВОЗВРАТОМ!!!)
    if (getKeyState(KEY_3) && isShift())
    {
        tumbler[TUMBLER_FAN3].set();
    }
    else
    {
        tumbler[TUMBLER_FAN4].reset();
    }

    // Вентилятор 4 (НЕ ФИКСИРУЕТСЯ!!! С ВОЗВРАТОМ!!!)
    if (getKeyState(KEY_4) && isShift())
    {
        tumbler[TUMBLER_FAN4].set();
    }
    else
    {
        tumbler[TUMBLER_FAN4].reset();
    }

    // Сигнализация
    if (getKeyState(KEY_5))
    {
        if (isShift())
        {
            tumbler[TUMBLER_SIGNAL_LIGHTS].set();
        }
        else
        {
            tumbler[TUMBLER_SIGNAL_LIGHTS].reset();
        }
    }

    // Автоматическая подсыпка песка
    if (getKeyState(KEY_6))
    {
        if (isShift())
        {
            tumbler[TUMBLER_SAND_AUTO].set();
        }
        else
        {
            tumbler[TUMBLER_SAND_AUTO].reset();
        }
    }
}
