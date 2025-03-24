#include    <pressure-contact-sensor.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
PressContactSensor::PressContactSensor(QObject *parent) : Device(parent)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
PressContactSensor::~PressContactSensor()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void PressContactSensor::preStep(state_vector_t &Y, double t)
{
    hysteresis.setValue(p);

    if (is_normal_off)
    {
        state = hysteresis.getState();
    }
    else
    {
        state = !hysteresis.getState();
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void PressContactSensor::ode_system(const state_vector_t &Y,
                                    state_vector_t &dYdt,
                                    double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void PressContactSensor::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    cfg.getDouble(secName, "p_min", p_min);
    cfg.getDouble(secName, "p_max", p_max);
    cfg.getBool(secName, "IsNormalOFF", is_normal_off);

    hysteresis.setRange(p_min, p_max);
}
