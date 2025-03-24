#ifndef     PRESSURE_CONTACT_SENSOR_H
#define     PRESSURE_CONTACT_SENSOR_H

#include    <device.h>
#include    <hysteresis.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class PressContactSensor : public Device
{
public:

    PressContactSensor(QObject *parent = Q_NULLPTR);

    ~PressContactSensor();

    void setPressure(double p)
    {
        this->p = p;
    }

    bool getState() const
    {
        return state;
    }

private:

    /// Текущее контролируемое давление
    double p = 0.0;

    /// Минимальное давление срабатывания
    double p_min = 0.0;

    /// Максимальное давление срабатывания
    double p_max = 0.0;

    /// Признак нормально разомкнутых контактов
    bool is_normal_off = true;

    /// Состояние контактор
    bool state = !is_normal_off;

    /// Функция, задающая гистерезис срабатывания датчика
    Hysteresis hysteresis;

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;
};

#endif // PRESSURE_CONTACT_SENSOR_H
