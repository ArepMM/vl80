#ifndef     VL80_SME_CONNECTOR_H
#define     VL80_SME_CONNECTOR_H

#include    "device.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class VL80SME : public Device
{
public:

    /// Конструктор
    VL80SME(QObject *parent = Q_NULLPTR);

    /// Деструктор
    ~VL80SME();

    /// Задать управляющую клавишу
    void setKeyCode(int key_code);

    /// Соединить межвагонные соединения
    void connect();

    /// Разъединить межвагонные соединения
    void disconnect();

    /// Состояние межвагонных соединений
    bool isConnected() const;

    /// Задать исходящий сигнал
    void setSignal(size_t idx, double value);

    /// Получить входящий сигнал
    double getSignal(size_t idx) const;

    void step(double t, double dt);

private:

    /// Код управляющей клавиши
    int keyCode = 0;

    /// Флаг вызова команд управления соединением
    bool is_ref_state_command;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t);

    void stepKeysControl(double t, double dt);
};

#endif // VL80_SME_CONNECTOR_H
