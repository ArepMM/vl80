#ifndef     SHIELD_215_H
#define     SHIELD_215_H

#include    <electric-module.h>
#include    <trigger.h>

/*!
 * \enum
 * \brief Номера входных проводов
 */
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
enum S215_InputWires
{
    S215_INPUTS_NUM = 3,
    S215_N0 = 0,
    S215_N119 = 1,
    S215_N113 = 2
};

/*!
 * \enum
 * \brief Номера выходных проводов
 */
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
enum S215_OutputWires
{
    S215_OUTPUTS_NUM = 16,
    S215_N01 = 0,
    S215_N02 = 1,
    S215_N03 = 2,
    S215_N04 = 3,
    S215_N05 = 4,
    S215_N06 = 5,
    S215_N122 = 6,
    S215_216 = 7,
    S215_N09 = 8,
    S215_N010 = 9,
    S215_N011 = 10,
    S215_N012 = 11,
    S215_N013 = 13,
    S215_N014 = 14,
    S215_E94 = 15
};

/*!
 * \class
 * \brief Щиток 215 (панель автоматов)
 */
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class Shield_215 : public ElectricModule
{
public:

    Shield_215(size_t input_wires_num = 1,
               size_t output_wires_num = 1,
               QObject *parent = Q_NULLPTR);

    ~Shield_215();

    /// Вернуть состояние автомата (для возможной анимации)
    bool getCircuitBreakerState(size_t cb_idx) const
    {
        if (cb_idx < circuit_breaker.size())
        {
            return circuit_breaker[cb_idx].getState();
        }

        return false;
    }

private:

    enum
    {
        /// Общее число автоматов
        CB_NUM = 14,
        /// Токоприемники
        VA1 = 0,
        /// Цепи управления
        VA2 = 1,
        /// Цепь торможения
        VA3 = 2,
        /// Главный контроллер
        VA4 = 3,
        /// Переключатели
        VA5 = 4,
        /// Локомотивная сигнализация
        VA6 = 5,
        VA7 = 6,
        /// Радиосвязь
        VA8 = 7,
        /// Фазоращепитель
        VA9 = 8,
        /// Вспомогательные машины
        VA10 = 9,
        /// Прожектор
        VA11 = 10,
        /// Фонари буферные
        VA12 = 11,
        /// Освещение и обогрев кабины
        VA13 = 12,
        /// Тифон, свисток, песок, резервуары
        VA14 = 13
    };

    /// Автоматические защитные выключатели
    std::array<Trigger, CB_NUM> circuit_breaker;

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                            state_vector_t &dYdt,
                            double t) override;

    void load_config(CfgReader &cfg) override;

    void stepKeysControl(double t, double dt) override;
};


#endif // SHIELD_215_H
