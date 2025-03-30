#ifndef     PNEUMO_SHUTOFF_VALVE_H
#define     PNEUMO_SHUTOFF_VALVE_H

#include    "device.h"

//------------------------------------------------------------------------------
// Разобщительный кран
//------------------------------------------------------------------------------
class /*DEVICE_EXPORT*/ PneumoShutoffValve : public Device
{
public:

    /// Конструктор
    PneumoShutoffValve(int key_code = 0, QObject *parent = Q_NULLPTR);

    /// Деструктор
    ~PneumoShutoffValve();

    /// Задать управляющую клавишу
    void setKeyCode(int key_code);

    /// Закрыть разобщительный кран
    void close();

    /// Открыть разобщительный кран
    void open();

    /// Cостояние разобщительного крана
    bool isOpened() const;

    /// Положение рукоятки: от 0.0 (кран закрыт) до 1.0 (кран открыт)
    float getHandlePosition() const;

    /// Задать давление со стороны магистрали
    void setPipePressure(double value);

    /// Давление со стороны оборудования
    double getPressureToDevice() const;

    /// Задать поток из оборудования
    void setDeviceFlow(double value);

    /// Поток в магистраль
    double getFlowToPipe() const;

    enum {
        NUM_SOUNDS = 4,
        CHANGE_SOUND = 0,   ///< Звук переключения разобщительного крана
        OPEN_SOUND = 1,     ///< Звук открытия разобщительного крана
        CLOSE_SOUND = 2,    ///< Звук перекрытия разобщительного крана
        PIPE_DRAIN_FLOW_SOUND = 3 ///< Звук выхода воздуха через атмосферное отверстие
    };
    /// Состояние звука
    sound_state_t getSoundState(size_t idx = CHANGE_SOUND) const;

    /// Сигнал состояния звука
    float getSoundSignal(size_t idx = CHANGE_SOUND) const;

private:

    enum {
        PRESSURE = 0    ///< Y[0] - Давление за разобщительным краном
    };

    /// Код управляющей клавиши
    int keyCode = 0;

    /// Давление в магистрали
    double p = 0.0;

    /// Поток из оборудования в магистраль
    double Q = 0.0;

    /// Поток выхода воздуха из оборудования через атмосферное отверстие
    double Q_atm = 0.0;

    /// Условный объём труб между краном и оборудованием
    double  V0 = 1.0e-3;

    /// Коэффициент к потоку выхода воздуха из оборудования в атмосферу при закрытом кране
    double K_atm = 0.0;

    /// Коэффициент громкости озвучки к потоку разрядки
    double K_sound = 2.0;

    /// Заданное состояние крана: 0 - закрыт, 1 - открыт
    Trigger ref_state;

    /// Звук выхода воздуха из оборудования через атмосферное отверстие
    sound_state_t atm_flow_sound = sound_state_t();

    void preStep(state_vector_t &Y, double t);

    void ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t);

    void load_config(CfgReader &cfg);

    void stepKeysControl(double t, double dt);
};

#endif // PNEUMO_SHUTOFF_VALVE_H
