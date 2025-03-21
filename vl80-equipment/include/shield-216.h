#ifndef     SHIELD_216_H
#define     SHIELD_216_H

#include    <electric-module.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class Shield_216 : public ElectricModule
{
public:

    Shield_216(size_t input_wires_num = 1,
               size_t output_wires_num = 1,
               QObject *parent = Q_NULLPTR);

    ~Shield_216();

    /// Вернуть состояние автомата (для возможной анимации)
    bool get_AZV_State(size_t azv_idx) const
    {
        if (azv_idx < azv.size())
        {
            return azv[azv_idx].getState();
        }

        return false;
    }

    enum S216_InputWires
    {
        INPUTS_NUM = 1,
        N0 = 0
    };

    enum S216_OutputWires
    {
        OUTPUTS_NUM = 5,
        N032 = 0,
        N033 = 1,
        N034 = 2,
        N035 = 3,
        N036 = 4
    };

    enum
    {
        /// Общее число автоматов
        AVZ_NUM = 5,
        VA32 = 0,
        VA33 = 1,
        VA34 = 2,
        VA35 = 3,
        VA36 = 4
    };

private:

    /// Автоматические защитные выключатели
    std::array<Trigger, AVZ_NUM> azv;

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;

    void stepKeysControl(double t, double dt) override;
};

#endif // SHIELD_216_H
