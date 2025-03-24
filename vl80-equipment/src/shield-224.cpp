#include    <shield-224.h>

// Сигналы для модели вл60к
#include    <vl80s-signals.h>

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
    output_wire[E18] =
        input_wire[N09] * static_cast<double>(tumbler[TUMBLER_AUX_MASHINES].getState());

    output_wire[E9] =
        input_wire[N09] * static_cast<double>(tumbler[TUMBLER_PHASE_SPLITTER].getState());

    output_wire[N102] =
        input_wire[N010] * static_cast<double>(tumbler[TUMBLER_COMPRESSORS].getState());

    output_wire[E21] =
        input_wire[N010] * static_cast<double>(tumbler[TUMBLER_FAN1].getState());

    output_wire[E22] =
        input_wire[N010] * static_cast<double>(tumbler[TUMBLER_FAN2].getState());

    output_wire[E23] =
        input_wire[N010] * static_cast<double>(tumbler[TUMBLER_FAN3].getState());

    output_wire[E24] =
        input_wire[N010] * static_cast<double>(tumbler[TUMBLER_FAN4].getState());

    output_wire[N400] =
        input_wire[N05] * static_cast<double>(tumbler[TUMBLER_SIGNAL_LIGHTS].getState());

    output_wire[E50] =
        input_wire[N010] * static_cast<double>(tumbler[TUMBLER_SAND_AUTO].getState());
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
    if (getKeyState(KEY_5))
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
        tumbler[TUMBLER_FAN3].reset();
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
    if (getKeyState(KEY_6))
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
    if (getKeyState(KEY_7))
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

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_224::stepSoundsSignals(double t, double dt)
{
    // !!!Сигналы в вл60к!!!
    (*analogSignal)[SOUND_TUMBLER_AUTOSAND_ON] = tumbler[TUMBLER_SAND_AUTO].getSoundSignal(Trigger::ON_SOUND);
    (*analogSignal)[SOUND_TUMBLER_FAN6_ON] = tumbler[TUMBLER_SIGNAL_LIGHTS].getSoundSignal(Trigger::ON_SOUND);
    (*analogSignal)[SOUND_TUMBLER_FAN5_ON] = tumbler[TUMBLER_FAN4].getSoundSignal(Trigger::ON_SOUND);
    (*analogSignal)[SOUND_TUMBLER_FAN4_ON] = tumbler[TUMBLER_FAN3].getSoundSignal(Trigger::ON_SOUND);
    (*analogSignal)[SOUND_TUMBLER_FAN3_ON] = tumbler[TUMBLER_FAN2].getSoundSignal(Trigger::ON_SOUND);
    (*analogSignal)[SOUND_TUMBLER_FAN2_ON] = tumbler[TUMBLER_FAN1].getSoundSignal(Trigger::ON_SOUND);
    (*analogSignal)[SOUND_TUMBLER_FAN1_ON] = tumbler[TUMBLER_COMPRESSORS].getSoundSignal(Trigger::ON_SOUND);
    (*analogSignal)[SOUND_TUMBLER_COMPRESSOR_ON] = tumbler[TUMBLER_PHASE_SPLITTER].getSoundSignal(Trigger::ON_SOUND);
    (*analogSignal)[SOUND_TUMBLER_PHASESPLITTER_ON] = tumbler[TUMBLER_AUX_MASHINES].getSoundSignal(Trigger::ON_SOUND);

    (*analogSignal)[SOUND_TUMBLER_AUTOSAND_OFF] = tumbler[TUMBLER_SAND_AUTO].getSoundSignal(Trigger::OFF_SOUND);
    (*analogSignal)[SOUND_TUMBLER_FAN6_OFF] = tumbler[TUMBLER_SIGNAL_LIGHTS].getSoundSignal(Trigger::OFF_SOUND);
    (*analogSignal)[SOUND_TUMBLER_FAN5_OFF] = tumbler[TUMBLER_FAN4].getSoundSignal(Trigger::OFF_SOUND);
    (*analogSignal)[SOUND_TUMBLER_FAN4_OFF] = tumbler[TUMBLER_FAN3].getSoundSignal(Trigger::OFF_SOUND);
    (*analogSignal)[SOUND_TUMBLER_FAN3_OFF] = tumbler[TUMBLER_FAN2].getSoundSignal(Trigger::OFF_SOUND);
    (*analogSignal)[SOUND_TUMBLER_FAN2_OFF] = tumbler[TUMBLER_FAN1].getSoundSignal(Trigger::OFF_SOUND);
    (*analogSignal)[SOUND_TUMBLER_FAN1_OFF] = tumbler[TUMBLER_COMPRESSORS].getSoundSignal(Trigger::OFF_SOUND);
    (*analogSignal)[SOUND_TUMBLER_COMPRESSOR_OFF] = tumbler[TUMBLER_PHASE_SPLITTER].getSoundSignal(Trigger::OFF_SOUND);
    (*analogSignal)[SOUND_TUMBLER_PHASESPLITTER_OFF] = tumbler[TUMBLER_AUX_MASHINES].getSoundSignal(Trigger::OFF_SOUND);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_224::stepAnimationsSignals(double t, double dt)
{
    // !!!Сигналы в вл60к!!!
    (*analogSignal)[91] = static_cast<float>(tumbler[TUMBLER_SAND_AUTO].getState());
    (*analogSignal)[TUMBLER_MV6] = static_cast<float>(tumbler[TUMBLER_SIGNAL_LIGHTS].getState());
    (*analogSignal)[TUMBLER_MV5] = static_cast<float>(tumbler[TUMBLER_FAN4].getState());
    (*analogSignal)[TUMBLER_MV4] = static_cast<float>(tumbler[TUMBLER_FAN3].getState());
    (*analogSignal)[TUMBLER_MV3] = static_cast<float>(tumbler[TUMBLER_FAN2].getState());
    (*analogSignal)[TUMBLER_MV2] = static_cast<float>(tumbler[TUMBLER_FAN1].getState());
    (*analogSignal)[TUMBLER_MV1] = static_cast<float>(tumbler[TUMBLER_COMPRESSORS].getState());
    (*analogSignal)[TUMBLER_MK] = static_cast<float>(tumbler[TUMBLER_PHASE_SPLITTER].getState());
    (*analogSignal)[TUMBLER_FR] = static_cast<float>(tumbler[TUMBLER_AUX_MASHINES].getState());
}
