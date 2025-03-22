#ifndef     PANEL_2_H
#define     PANEL_2_H

#include    <electric-module.h>
#include    <relay.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class Panel_2 : public ElectricModule
{
public:

    Panel_2(size_t input_wires_num = 1,
            size_t output_wires_num = 1,
            QObject *parent = Q_NULLPTR);

    ~Panel_2();

    void step(double t, double dt) override;

    void init(const QString &custom_cfg_dir);

    enum P2_InputWires
    {
        INPUTS_NUM = 1
    };

    enum P2_OutputWires
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

#endif // PANEL_2_H
