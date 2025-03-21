#ifndef     SHIELD_210_H
#define     SHIELD_210_H

#include    <electric-module.h>
#include    <relay.h>
#include    <trigger.h>

/*!
 * \class
 * \brief Щиток 210 (распределительный щит)
 */
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class Shield_210 : public ElectricModule
{
public:

    Shield_210(size_t input_wires_num = 1,
               size_t output_wires_num = 1,
               QObject *parent = Q_NULLPTR);

    ~Shield_210();

    enum S210_InputWires
    {
        INPUTS_NUM = 3,
        /// Вход питания от АКБ
        N113 = 0,
        /// Вход питания ЦУ от 2 секции
        SME_E62 = 1,
        /// Вход питания ЦУ от 2 секции
        SME_E66 = 2
    };

    enum S210_OutputtWires
    {
        OUTPUT_NUM = 9,
        N119 = 0,
        N0 = 1,
        N49 = 2,
        N401 = 3,
        N402 = 4,
        N66 = 5,
        /// Выход питания ЦУ на 2 секцию
        E61 = 6,
        /// Выход питания ЦУ на 2 секцию
        E65 = 7,
        N116 = 8
    };

    void init(const QString &custom_cfg_dir);

    void step(double t, double dt) override;

    /// Задать напряжение питания от обмотки собственных нужд
    void setVoltageAC(double Uac)
    {
        this->Uac = Uac;
    }


    /// Задать ток нагрузки
    void setLoadCurrent(double I_load)
    {
        this->I_load = I_load;
    }

    /// Ток нагрузки АКБ
    double getBatteryCurrent() const
    {
        return I_bat;
    }

private:

    /// Рубильник подключения батареи
    Trigger switch_2R;

    /// Рубильник режима работы (нормально/аварийно)
    Trigger switch_3R;

    enum
    {
        K_NUM_CONTACTS = 3,
        K_9_21 = 0,
        K_31_32 = 1,
        K_16_17 = 2
    };

    /// Контактор питания от батареи
    Relay *K = new Relay(K_NUM_CONTACTS);

    /// Ток, потребляемый нагрузкой
    double I_load = 0.0;

    /// Эквивалентное внутреннее сопротивление выпрямителя
    double r = 0.03;

    /// Коэффициент трансформации выпрямителя
    double K_rect = 0.18;

    /// Напряжение на выходе выпрямителя
    double U_rect = 0.0;

    /// Коэффициент передачи регулятора напряжения
    double K_u = 1.0;

    /// Постоянная времени переходного процесса в выпрямителе
    double T_rect = 0.1;

    /// Уставка напряжения питания ЦУ и заряда АКБ
    double U_ref = 60.0;

    /// Заданная величина ЭДС выпрямителя
    double E_ref;

    /// Напряжение питания от обмотки собственных нужд тягового трансформатора
    double Uac = 0.0;

    /// Ток нагрузки аккумуляторной батареи
    double I_bat = 0.0;

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;

    void stepKeysControl(double t, double dt) override;
};


#endif // SHIELD_210_H
