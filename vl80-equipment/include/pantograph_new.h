#ifndef PANTOGRAPH_NEW_H
#define PANTOGRAPH_NEW_H

#include    "device.h"
#include    "trigger.h"

//------------------------------------------------------------------------------
// Токоприемник пантографного типа
//------------------------------------------------------------------------------
class /*DEVICE_EXPORT*/ Pantograph_new : public Device
{

public:

    /// Конструктор
    Pantograph_new(QObject *parent = Q_NULLPTR);

    /// Деструктор
    ~Pantograph_new();

    // TODO // Заготовка под взаимодействие с путевой инфраструктурой
    enum
    {
        SIZE_OF_OUTPUTS = 1,    ///< Размер массива исходящих сигналов

        OUTPUT_CURRENT = 0,     ///< Ток, потребляемый из контактной сети, А

        SIZE_OF_INPUTS = 3,     ///< Размер массива входящих сигналов

        INPUT_WIRE_HEIGHT = 0,  ///< Высота контактного провода, м
        INPUT_VOLTAGE = 1,      ///< Напряжение в контактной сети, В
        INPUT_FREQUENCY = 2,    ///< Частота тока в контактной сети, Гц
    };

    /// Задать ток, потребляемый из контактной сети, А
    void setCurrent(double I);

    /// Задать давление в магистрали к цилиндру пневмопривода токоприёмника, МПа
    void setPneumodriveRefPressure(double p);

    /// Задать высоту контактного провода, м
    void setWireHeight(double h);

    /// Задать напряжение в контактной сети, В
    void setVoltage(double U);

    /// Задать частоту тока в контактной сети, Гц
    void setFrequency(double f);

    /// Поток воздуха в магистраль из цилиндра пневмопривода токоприёмника
    double getPneumodriveFlow() const;

    /// Напряжение на выходе токоприёмника, В
    double getVoltage() const;

    /// Частота тока на выходе токоприёмника, Гц
    double getFrequency() const;

    /// Высота полоза токоприёмника, м
    double getHeight() const;

    /// Относительная высота токоприёмника, д.е.
    double getRelativeHeight() const;

    // TODO // Переделать озвучку - отделить звуки касания провода и складывания
    enum {
        NUM_SOUNDS = 3,
        CHANGE_SOUND = 0,
        UP_SOUND = 1,
        DOWN_SOUND = 2
    };
    /// Состояние звука
    sound_state_t getSoundState(size_t idx = CHANGE_SOUND) const;

    /// Сигнал состояния звука
    float getSoundSignal(size_t idx = CHANGE_SOUND) const;

private:

    enum {
        PRESSURE = 0,   ///< Y[0] - Давление пневмопривода токоприёмника, МПа
        HEIGHT = 1      ///< Y[1] - Высота полоза токоприёмника, м
    };

    /// Объём цилиндра пневмопривода токоприёмника, м^3
    double Vc = 0.01;

    /// Коэффициент перетока воздуха из магистрали в цилиндр пневмопривода
    double Kc = 0.01;

    /// Давление в магистрали к цилиндру пневмопривода токоприёмника, МПа
    double pc = 0.0;

    /// Поток воздуха в магистраль из цилиндра пневмопривода токоприёмника
    double Qc = 0.0;

    /// Минимальное давление срабатывания пневмопривода токоприёмника, МПа
    double Pmin = 0.35;

    /// Номинальное давление пневмопривода токоприёмника, МПа
    double Pnom = 0.5;

    /// Время поднятия токоприёмника при номинальном / опускания при нулевом давлении, с
    double motion_time = 7.0;

    /// Высота полоза в опущенном состоянии, м
    double height_down = 5.1;

    /// Максимальная высота полоза в поднятом состоянии, м
    double height_up = 7.0;

    /// Номинальная скорость поднятия / опускания токоприёмника, м/с
    double motion_v_nom = (7.0 - 5.1) / 7.0;

    /// Признак касания полоза и контактного провода
    bool is_contact = false;

    /// Допустимая разница высоты полоза и провода, при которой считается касание, м
    const double eps = 0.05;

    // TODO // Переделать озвучку - отделить звуки касания провода и складывания
    /// Озвучка состояния токоприемника (true - поднимается, false - опускается)
    Trigger ref_state;

    void ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t);

    void load_config(CfgReader &cfg);

};

#endif // PANTOGRAPH_NEW_H
