#include    "pneumo-shutoff-valve.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
PneumoShutoffValve::PneumoShutoffValve(int key_code, QObject *parent) : Device(parent)
    , keyCode(key_code)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
PneumoShutoffValve::~PneumoShutoffValve()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void PneumoShutoffValve::setKeyCode(int key_code)
{
    keyCode = key_code;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void PneumoShutoffValve::close()
{
    ref_state.reset();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void PneumoShutoffValve::open()
{
    ref_state.set();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool PneumoShutoffValve::isOpened() const
{
    return is_opened;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double PneumoShutoffValve::getHandlePosition() const
{
    return getY(STATE);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void PneumoShutoffValve::setPipePressure(double value)
{
    p = value;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double PneumoShutoffValve::getPressureToDevice() const
{
    return getY(PRESSURE);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void PneumoShutoffValve::setDeviceFlow(double value)
{
    Q = value;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double PneumoShutoffValve::getFlowToPipe() const
{
    if (is_opened)
        return getY(STATE) * Q;
    return 0.0;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
sound_state_t PneumoShutoffValve::getSoundState(size_t idx) const
{
    if (idx == PIPE_DRAIN_FLOW_SOUND)
        return atm_flow_sound;
    return ref_state.getSoundState(idx);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
float PneumoShutoffValve::getSoundSignal(size_t idx) const
{
    if (idx == PIPE_DRAIN_FLOW_SOUND)
        return atm_flow_sound.createSoundSignal();
    return ref_state.getSoundSignal(idx);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void PneumoShutoffValve::preStep(state_vector_t &Y, double t)
{
    (void) t;

    if (Y[STATE] < 0.05)
    {
        is_opened = false;
        atm_flow_sound.state = 1;
        atm_flow_sound.volume = K_sound * cbrt(getY(STATE) * Q);
    }
    else
    {
        is_opened = true;
        atm_flow_sound.state = 0;
        atm_flow_sound.volume = 0.0f;
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void PneumoShutoffValve::ode_system(const state_vector_t &Y,
                                    state_vector_t &dYdt,
                                    double t)
{
    (void) t;

    // Перемещение рукоятки
    double ref_pos = static_cast<double>(ref_state.getState());
    double delta = ref_pos - Y[STATE];
    if (abs(delta) > 0.05)
    {
        dYdt[STATE] = sign(delta) / switch_time;
    }
    else
    {
        dYdt[STATE] = 20.0 * delta / switch_time;
    }

    // Давление в трубах между краном и оборудованием
    if (Y[STATE] > 0.95)
    {
        setY(PRESSURE, p);
        dYdt[PRESSURE] = 0.0;
    }
    else
    {
        double flow_device = (1.0 - Y[STATE]) * Q;
        double flow_atm = (1.0 - Y[STATE]) * Y[PRESSURE] * K_atm;
        dYdt[PRESSURE] = (flow_device - flow_atm) / V0;
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void PneumoShutoffValve::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    bool state = false;
    cfg.getBool(secName, "IsOpened", state);
    state ? ref_state.set() : ref_state.reset();

    double tmp = 0.0;
    cfg.getDouble(secName, "V0", tmp);
    if (tmp > 1e-3)
        V0 = tmp;

    cfg.getDouble(secName, "K_atm", K_atm);

    cfg.getDouble(secName, "K_sound", K_sound);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void PneumoShutoffValve::stepKeysControl(double t, double dt)
{
    (void) t;

    // Проверяем управляющий сигнал
    if (getKeyState(keyCode))
    {
        if (isShift() && (!isControl()))
        {
            // Открываем разобщительный кран
            open();
        }
        else
        {
            if (isControl())
                // Закрываем разобщительный кран
                close();
        }
    }
}
