#ifndef     ELECTRIC_MODULE_H
#define     ELECTRIC_MODULE_H

#include    <device.h>
#include    <vehicle-signals.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
using wire_t = std::vector<double>;

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
using analog_signals_t = std::array<float, MAX_ANALOG_SIGNALS>;

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class ElectricModule : public Device
{
public:

    ElectricModule(size_t input_wires_num = 1,
                   size_t output_wires_num = 1,
                   QObject *parent = Q_NULLPTR);

    ~ElectricModule();

    /// Задать напряжение на входном проводе
    void setInputVoltage(size_t wire_idx, double U)
    {
        if (wire_idx < input_wire.size())
        {
            input_wire[wire_idx] = U;
        }
    }

    /// Получить напряжение с выходного провода
    double getOutputVoltage(size_t wire_idx) const
    {
        if (wire_idx < output_wire.max_size())
        {
            return output_wire[wire_idx];
        }

        return 0.0;
    }

    /// Получить напряжение с входного провода
    double getIutputVoltage(size_t wire_idx) const
    {
        if (wire_idx < input_wire.max_size())
        {
            return input_wire[wire_idx];
        }

        return 0.0;
    }

    /// Вернуть ток, потребляемый модулем
    double getCurrent() const
    {
        return Icc;
    }

    virtual void step(double t, double dt);

    void setAnalogSignalsPtr(analog_signals_t *analogSignal)
    {
        this->analogSignal = analogSignal;
    }

protected:

    /// Входные электрические линии
    wire_t input_wire;

    /// Выходные электрические линии
    wire_t output_wire;

    /// Ток, потребляемый модулем
    double Icc = 0.0;

    /// Указатель на массив аналоговых сигналов
    analog_signals_t *analogSignal = nullptr;

    virtual void preStep(state_vector_t &Y, double t);

    virtual void ode_system(const state_vector_t &Y,
                            state_vector_t &dYdt,
                            double t);

    virtual void load_config(CfgReader &cfg);

    virtual void stepKeysControl(double t, double dt);

    /// Вывод сигналов для воспроизведения звуков
    virtual void stepSoundsSignals(double t, double dt);

    /// Вывод сигналов для воспроизведения анимаций
    virtual void stepAnimationsSignals(double t, double dt);
};

#endif // ELECTRIC_MODULE_H
