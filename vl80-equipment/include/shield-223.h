#ifndef     SHIELD_223_H
#define     SHIELD_223_H

#include    <electric-module.h>
#include    <trigger.h>

/*!
 * \class
 * \brief Щиток 223 - дальний "рояль"
 */
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class Shield_223 : public ElectricModule
{
public:

    Shield_223(size_t input_wires_num = 1, size_t output_wires_num = 1,
               QObject *parent = Q_NULLPTR);

    ~Shield_223();

    enum S223_InputWires
    {
        INPUTS_NUM = 5,
        N01 = 0,
        N02 = 1,
        N011 = 2,
        SME_E16 = 3,
        SME_E17 = 4
    };

    enum S223_OutputWires
    {
        OUTPUTS_NUM = 8,
        N88 = 0,
        E14 = 1,
        E15 = 2,
        E16 = 3,
        E17 = 4,
        E1 = 5,
        N151 = 6,
        N152 = 7
    };

    enum
    {
        TUMBLERS_NUM = 8,
        /// Выключение ГВ
        TUMBLER_GV_OFF = 0,
        /// Включение ГВ и возврат защиты
        TUMBLER_GV_ON = 1,
        /// Токоприемники
        TUMBLER_PANTS = 2,
        /// Токоприемник передний
        TUMBLER_PANT_FWD = 3,
        /// Токоприемник задний
        TUMBLER_PANT_BWD = 4,
        /// Цепи управления
        TUMBLER_CTRL_CIRCUIT = 5,
        /// Прожектор тускло
        TUMBLER_SPOT_LIGHT = 6,
        /// Прожектор ярко
        TUMBLER_SPOT_LIGHT_BRIGHT = 7
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

    /// Тумблеры на щитке
    std::array<Trigger, TUMBLERS_NUM> tumbler;

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;

    void stepKeysControl(double t, double dt) override;
};

#endif // SHIELD_223_H
