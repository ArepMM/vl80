#ifndef     PANEL_9_H
#define     PANEL_9_H

#include    <electric-module.h>
#include    <relay.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class Panel_9 : public ElectricModule
{
public:

    Panel_9(size_t input_wires_num = 1,
            size_t output_wires_num = 1,
            QObject *parent = Q_NULLPTR);

    ~Panel_9();

    void step(double t, double dt) override;

    void init(const QString &custom_cfg_dir);

    enum P9_InputWires
    {
        INPUTS_NUM = 20,
        E37 = 0,
        E16 = 1,
        E13 = 2
    };

    enum P9_OutputWires
    {
        OUTPUTS_NUM = 20,
        N125 = 0,
        N68 = 1
    };

private:

    enum
    {
        K248_NUM_CONTACTS = 2,
        K248_E16_N125 = 0,
        K248_E13_N68 = 1
    };

    Relay *K248 = new Relay(K248_NUM_CONTACTS);

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;

    void stepKeysControl(double t, double dt) override;
};

#endif // PANEL_9_H
