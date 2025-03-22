#ifndef     PANEL_6_H
#define     PANEL_6_H

#include    <electric-module.h>
#include    <relay.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class Panel_6 : public ElectricModule
{
public:

    Panel_6(size_t input_wires_num = 1,
            size_t output_wires_num = 1,
            QObject *parent = Q_NULLPTR);

    ~Panel_6();

    void step(double t, double dt) override;

    void init(const QString &custom_cfg_dir);

    enum P6_InputWires
    {
        INPUTS_NUM = 1
    };

    enum P6_OutputWires
    {
        OUTPUTS_NUM = 1
    };

private:

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;

    void stepKeysControl(double t, double dt) override;
};

#endif // PANEL_6_H
