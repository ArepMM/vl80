#ifndef     DC_MOTOR_H
#define     DC_MOTOR_H

#include    <device.h>

/*!
 * \class
 * \brief Универсальная модель двигателя постоянного тока для всех типов возбуждения
 */
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class DCMotor : public Device
{
public:

    DCMotor(QObject *parent = Q_NULLPTR);

    ~DCMotor();

    /// Тип возбуждения
    enum FieldMode
    {
        /// Последовательное
        SERIES = 0,
        /// Параллельное
        PARALLEL = 1,
        /// Независимое
        IDEPENDENT = 2
    };

protected:

    /// Напряжение на обмотке якоря
    double Ua = 0.0;

    /// Напряжение на обмотке возбуждения
    double Uf = 0.0;

    /// Сопротивление обмотки якоря
    double Ra = 1.0;

    /// Сопротивление обмотки возбуждения
    double Rf = 1.0;

    /// Постоянная времени нарастания тока в обмотке якоря
    double Ta = 0.2;

    /// Постоянная времени нарастания тока в обмотке возбуждения
    double Tf = 0.2;

    /// Значение кривой намагничивания в номинальном режиме
    double cPhi_nom = 0.1;

    /// Угловая скорость вращения вала
    double omega = 0.0;

    /// Номинальное напряжение
    double U_nom = 10.0;

    /// Номинальный ток
    double Inom = 2.0;

    /// Порядок аппроксимирующего полинома кривой намагничивания
    enum
    {
        APPROX_ORDER = 5
    };

    /// Коэффициенты аппроксимации универсальной кривой номагничивания
    /// полиномом 5-го порядка (нормированы к номинальным параметрам)
    std::array<double, APPROX_ORDER> a = {2.61, -3.00, 1.97, -0.66, 0.09};


    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;

    /// Расчет значения кривой намагничивания
    double cPhi(double If);
};

#endif // DC_MOTOR_H
