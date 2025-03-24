#ifndef     COMPRESSOR_H
#define     COMPRESSOR_H

#include    <device.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class Compressor : public Device
{
public:

    Compressor(QObject *parent = Q_NULLPTR);

    ~Compressor();

    /// Задать момент привода
    void setActorTorque(double M)
    {
        this->M = M;
    }

    /// Получить угловую скорость входного вала
    double getOmega() const
    {
        return getY(0) * ip;
    }

    /// Задать внешнее давление
    void setOutputPressure(double p_out)
    {
        this->p_out = p_out;
    }

    /// Получить расход воздуха на выходе
    double getQ_out() const
    {
        return Q_out;
    }

private:

    /// Момент, передаваемый от двигателя
    double M = 0.0;

    /// Статический момент сопротивления движению
    double Mxx = 0.0;

    /// Передаточное число редуктора
    double ip = 1.0;

    /// Приверенный к валу момент инерции
    double J = 1.0;

    /// Давление воздуха в магистрали, куда происходит нагнетание
    double p_out = 0.0;

    /// Расход воздуха на выходе
    double Q_out = 0.0;

    /// Отношение длины шатуна к длине кривошипа
    double lambda = 2.0;

    /// Максимальная степень сжатия воздуха
    double eps = 10.0;

    /// Эквивалентная площадь поршня
    double S = 0.1;

    /// Ход поншня
    double h = 0.045;

    /// Показатель адиабатты
    const double gamma = 1.4;

    /// Коэффициент расхода
    double K_flow = 1.0;

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;
};

#endif // COMPRESSOR_H
