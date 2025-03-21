#ifndef     SHIELD_215_H
#define     SHIELD_215_H

#include    <electric-module.h>
#include    <trigger.h>

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
        if (cb_idx < azv.size())
        {
            return azv[cb_idx].getState();
        }

        return false;
    }

    /*!
     * \enum
     * \brief Номера входных проводов
     */
    enum S215_InputWires
    {
        INPUTS_NUM = 3,
        N0 = 0,
        N119 = 1,
        N113 = 2
    };

    /*!
     * \enum
     * \brief Номера выходных проводов
     */
    enum S215_OutputWires
    {
        OUTPUTS_NUM = 16,
        N01 = 0,
        N02 = 1,
        N03 = 2,
        N04 = 3,
        N05 = 4,
        N06 = 5,
        N122 = 6,

        N09 = 8,
        N010 = 9,
        N011 = 10,
        N012 = 11,
        N013 = 13,
        N014 = 14,
        E94 = 15
    };

    /*!
     * \enum
     * \brief Автоматические защитные выключатели
     */
    enum
    {
        /// Общее число автоматов
        AVZ_NUM = 14,
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


#endif // SHIELD_215_H
