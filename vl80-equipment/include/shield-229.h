#ifndef     SHIELD_229_H
#define     SHIELD_229_H

#include    <electric-module.h>
#include    <trigger.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class Shield_229 : public ElectricModule
{
public:

    Shield_229(size_t input_wires_num = 1,
               size_t output_wires_num = 1,
               QObject *parent = Q_NULLPTR);

    ~Shield_229();

    enum
    {
        TUMBLERS_NUM = 1,
        TUMBLER_SAND = 0
    };

    enum S229_InputWires
    {
        INPUTS_NUM = 1,
        N014 = 0
    };

    enum S229_OutputWires
    {
        OUTPUTS_NUM = 1,
        E36 = 0
    };

    /// Вернуть положение тумблеров
    float getTumblerPos(size_t idx) const
    {
        if (idx >= tumbler.size())
        {
            return 0.0f;
        }

        return static_cast<float>(tumbler[idx].getState());
    }

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

#endif // SHIELD_229_H
