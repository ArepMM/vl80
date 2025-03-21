#ifndef     SHIELD_224_H
#define     SHIELD_224_H

#include    <electric-module.h>
#include    <trigger.h>

/*!
 * \class
 * \brief Щиток 224 - ближний "рояль"
 */
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class Shield_224 : public ElectricModule
{
public:

    Shield_224(size_t input_wires_num = 1,
               size_t output_wires_num = 1,
               QObject *parent = Q_NULLPTR);

    ~Shield_224();

    enum S224_InputWires
    {
        INPUTS_NUM = 3,
        N09 = 0,
        N010 = 1,
        N05 = 2
    };

    enum S224_OutputWires
    {
        OUTPUTS_NUM = 8,
        E18 = 0,
        E9 = 1,
        N102 = 2,
        E21 = 3,
        E22 = 4,
        E23 = 5,
        E24 = 6,
        N400 = 7
    };

    enum
    {
        TUMBLERS_NUM = 9,
        /// Вспомогательные машины
        TUMBLER_AUX_MASHINES = 0,
        /// Фазоращепитель
        TUMBLER_PHASE_SPLITTER = 1,
        /// Компрессоры
        TUMBLER_COMPRESSORS = 2,

        /// Вентилятор 1
        TUMBLER_FAN1 = 3,

        /// Вентилятор 2
        TUMBLER_FAN2 = 4,

        /// Вентилятор 3
        TUMBLER_FAN3 = 5,

        /// Вентилятор 4
        TUMBLER_FAN4 = 6,

        /// Сигнализация
        TUMBLER_SIGNAL_LIGHTS = 7,
        /// Автоматическая подсыпка песка
        TUMBLER_SAND_AUTO = 8
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

#endif // SHIELD_224_H
