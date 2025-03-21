#ifndef     SHIELD_225_H
#define     SHIELD_225_H

#include    <electric-module.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class Shield_225 : public ElectricModule
{
public:

    Shield_225(size_t input_wires_num = 1,
               size_t output_wires_num = 1,
               QObject *parent = Q_NULLPTR);

    ~Shield_225();

    enum
    {
        TUMBLERS_NUM = 15,
        /// Локомотивная сигнализация
        TUMBLER_LOCO_SIGNALING = 0,
        /// Проверка АЛСН
        TUMBLER_CHECK_ALSN = 1,
        /// Фонарь буферный правый
        TUMBLER_TAILLIGHT_RIGHT = 2,
        /// Фонарь буферный левый
        TUMBLER_TAILLIGHT_LEFT = 3,
        /// Освещение измерительных приборов
        TUMBLER_GAUGES_LIGHT = 4,
        /// Освещение тележек
        TUMBLER_BOGIE_LIGHT = 5,
        /// Ярокое освещение кабины
        TUMBLER_CAB_LIGHT_HIGH = 6,
        /// Тусклое освещение кабины
        TUMBLER_CAB_LIGHT_LOW = 7,
        /// Обогрев кабины 2 печи
        TUMBLER_CAB_HEAT_2 = 8,
        /// Обогрев кабины 3 печи
        TUMBLER_CAB_HEAT_3 = 9,
        /// Свисток
        TUMBLER_SVISTOK = 10,
        /// Тифон
        TUMBLER_TIFON = 11,
        /// Освещение документов
        TUMBLER_DOCS_LIGHT1 = 12,
        /// Освещение документов
        TUMBLER_DOCS_LIGHT2 = 13,
        /// ОСвещение зеленый свет
        TUMBLER_GREEN_LIGHT = 14
    };

    enum S225_InputWires
    {
        INPUTS_NUM = 4,
        N012 = 0,
        N013 = 1,
        N014 = 2,
        N033 = 3
    };

    enum S225_OutputWires
    {
        OUTPUTS_NUM = 13,
        N153 = 0,
        N154 = 1,
        N155 = 2,
        N453 = 3,
        N163 = 4,
        N164 = 5,
        N160 = 6,
        N161 = 7,
        N178 = 8,
        E57 = 9,
        N139 = 10,
        N159 = 11,
        N145 = 12
    };

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

#endif // SHIELD_225_H
