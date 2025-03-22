#ifndef     SHIELD_228_H
#define     SHIELD_228_H

#include    <electric-module.h>
#include    <trigger.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class Shield_228 : public ElectricModule
{
public:

    Shield_228(size_t input_wires_num = 1,
               size_t output_wires_num = 1,
               QObject *parent = Q_NULLPTR);

    ~Shield_228();

    enum
    {
        TUMBLERS_NUM = 3,
        TUMBLER_SVISTOK = 0,
        TUMBLER_TIFON = 1,
        TUMBLER_SAND = 2,
    };

    enum S228_InputWires
    {
        INPUTS_NUM = 1,
        N014 = 0
    };

    enum S228_OutputWires
    {
        OUTPUTS_NUM = 3,
        N178 = 0,
        E57 = 1,
        E36 = 2
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

#endif // SHIELD_228_H

