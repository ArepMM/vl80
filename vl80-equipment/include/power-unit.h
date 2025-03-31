#ifndef     POWER_UNIT_H
#define     POWER_UNIT_H

#include    <electric-module.h>
#include    <relay.h>
#include    <trigger.h>

/*!
 * \class
 * \brief Блок силовых аппаратов (БСА)
 */
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class PowerUnit : public ElectricModule
{
public:

    PowerUnit(size_t input_wires_num = 1,
            size_t output_wires_num = 1,
            QObject *parent = Q_NULLPTR);

    ~PowerUnit();

    void step(double t, double dt) override;

    void init(const QString &custom_cfg_dir);

    enum PU_InputWires
    {
        INPUTS_NUM = 1,
        E15 = 0
    };

    enum PU_OutputWires
    {
        OUTPUTS_NUM = 2,
        N43 = 0,
        N44 = 1
    };

private:

    /// Разъеденитель контактных шин 19
    Trigger S19;

    /// Разъеденитель контактных шин 19
    Trigger S20;

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;

    void stepKeysControl(double t, double dt) override;
};

#endif // POWER_UNIT_H
