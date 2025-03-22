#ifndef     SHIELD_226_H
#define     SHIELD_226_H

#include    <electric-module.h>
#include    <trigger.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class Shield_226 : public ElectricModule
{
public:

    Shield_226(size_t input_wires_num = 1,
               size_t output_wires_num = 1,
               QObject *parent = Q_NULLPTR);

    ~Shield_226();

    enum
    {
        TUMBLERS_NUM = 3,
        TUMBLER_COMPRESSOR = 0,
        TUMBLER_FAN2 = 1,
        TUMBLER_FAN4 = 2,
    };

    enum S226_InputWires
    {
        INPUTS_NUM = 3,
        N010 = 0,
        N512 = 1,
        N514 = 2
    };

    enum S226_OutputWires
    {
        OUTPUTS_NUM = 3,
        N104 = 0,
        N128 = 1,
        N132 = 2
    };

private:

    // Тумблеры на щитке
    std::array<Trigger, TUMBLERS_NUM> tumbler;

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;

    void stepKeysControl(double t, double dt) override;
};

#endif // SHIELD_226_H
