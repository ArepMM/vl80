#ifndef     KM_84_H
#define     KM_84_H

#include    <device.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class ControllerKM84 : public Device
{
public:

    ControllerKM84(QObject *parent = Q_NULLPTR);

    ~ControllerKM84();

private:

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;

    void stepKeysControl(double t, double dt) override;
};

#endif
