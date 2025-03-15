#ifndef     ELECTRIC_MODULE_H
#define     ELECTRIC_MODULE_H

#include    <device.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class ElectricModule : public Device
{
public:

    ElectricModule(QObject *parent = Q_NULLPTR);

    ~ElectricModule();

protected:

    virtual void preStep(state_vector_t &Y, double t);

    virtual void ode_system(const state_vector_t &Y,
                            state_vector_t &dYdt,
                            double t);

    virtual void load_config(CfgReader &cfg);

    virtual void stepKeysControl(double t, double dt);
};

#endif // ELECTRIC_MODULE_H
