#ifndef     SELSYN_H
#define     SELSYN_H

#include    <electric-module.h>

/*!
 * \class
 * \brief Сельсин БД-404А - задатчик скорости для реостатного тормоза
 */
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class Selsyn : public ElectricModule
{
public:

    Selsyn(size_t input_wires_num = 1,
                   size_t output_wires_num = 1,
                   QObject *parent = Q_NULLPTR);

    ~Selsyn();

private:

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;
};

#endif // SELSYN_H
