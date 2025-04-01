#ifndef     MODE_SWITCH_H
#define     MODE_SWITCH_H

#include    <electric-module.h>
#include    <pneumo-electro-valve.h>

/*!
 * \class
 * \brief Переключатель режимов (ПР)
 */
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class ModeSwitch : ElectricModule
{
public:

    ModeSwitch(size_t input_wires_num = 1,
            size_t output_wires_num = 1,
            QObject *parent = Q_NULLPTR);

    ~ModeSwitch();

    void step(double t, double dt) override;

    void init(const QString &custom_cfg_dir);

    enum MS_InputWires
    {
        INPUTS_NUM = 20,
        E110 = 0,
        E131 = 1,
        E13 = 2
    };

    enum MS_OutputWires
    {
        OUTPUTS_NUM = 20,
        N68 = 0
    };

private:

    /// Вентиль включения
    PneumoElectroValve on_valve = new PneumoElectroValve;

    /// Вентиль выключения
    PneumoElectroValve off_valve = new PneumoElectroValve;

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;

    void stepKeysControl(double t, double dt) override;
};

#endif // MODE_SWITCH_H
