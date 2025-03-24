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
    return ref_state.getState();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
float PneumoShutoffValve::getHandlePosition() const
{
    return static_cast<float>(ref_state.getState());
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
    if (ref_state.getState())
        return Q;
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

    if (ref_state.getState())
    {
        Q_atm = 0.0;
        atm_flow_sound.state = 0;
        atm_flow_sound.volume = 0.0f;
    }
    else
    {
        Q_atm = K_atm * Y[PRESSURE];
        atm_flow_sound.state = 1;
        atm_flow_sound.volume = K_sound * cbrt(Q_atm);
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

    if (ref_state.getState())
    {
        setY(PRESSURE, p);
        dYdt[PRESSURE] = 0.0;
    }
    else
    {
        dYdt[PRESSURE] = (Q - Q_atm) / V0;
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
