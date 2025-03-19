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
    return getY(0);
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
    return getY(1);
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
    return getY(0) * Q;
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

    if (Y[0] < 0.05)
    {
        is_opened = false;
        atm_flow_sound.state = 1;
        atm_flow_sound.volume = K_sound * cbrt(Q);
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
    double delta = ref_pos - Y[0];
    if (abs(delta) > 0.05)
    {
        dYdt[0] = sign(delta) / switch_time;
    }
    else
    {
        dYdt[0] = 20.0 * delta / switch_time;
    }

    // Давление в трубах между краном и оборудованием
    if (Y[0] > 0.95)
    {
        setY(1, p);
        dYdt[1] = 0.0;
    }
    else
    {
        double flow_device = (1.0 - Y[0]) * Q;
        double flow_atm = (1.0 - Y[0]) * Y[1] * K_atm;
        dYdt[1] = (flow_device - flow_atm) / V0;
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void PneumoShutoffValve::load_config(CfgReader &cfg)
{
    QString secName = "Device";

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
