#ifndef     SELSYN_BD_404A_H
#define     SELSYN_BD_404A_H

#include    <electric-module.h>

/*!
 * \class
 * \brief Сельсин БД-404А - задатчик скорости для реостатного тормоза
 */
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class Selsyn_BD_404A : public ElectricModule
{
public:

    Selsyn_BD_404A(size_t input_wires_num = 1,
                   size_t output_wires_num = 1,
                   QObject *parent = Q_NULLPTR);

    ~Selsyn_BD_404A();

private:

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;
};

#endif // SELSYN_BD_404A_H
