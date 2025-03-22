#ifndef     PANEL_1_H
#define     PANEL_1_H

#include    <electric-module.h>
#include    <relay.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class Panel_1 : public ElectricModule
{
public:

    Panel_1(size_t input_wires_num = 1,
            size_t output_wires_num = 1,
            QObject *parent = Q_NULLPTR);

    ~Panel_1();

    void step(double t, double dt) override;

private:

    /// Контакты К160
    enum
    {
        K160_NUM_CONTACTS = 2,
        K160_C12_C111 = 0,
        K160_C12_C112 = 1
    };

    /// Контактор ТРПШ
    Relay *K160 = new Relay(K160_NUM_CONTACTS);

    /// Контакты К159
    enum
    {
        K159_NUM_CONTACTS = 1,
        K159_C219_C2 = 0
    };

    /// 2 печи
    Relay *K159 = new Relay(K159_NUM_CONTACTS);

    /// Контакты К134
    enum
    {
        K134_NUM_CONTACTS = 1,
        K134_C2_C218 = 0
    };

    /// 3 печи
    Relay *K134 = new Relay(K134_NUM_CONTACTS);

    /// Контакты К119
    enum
    {
        K119_NUM_CONTACTS = 3,
        K119_N107_N103 = 0,
        K119_C101_C130 = 1,
        K119_C302_C303 = 2,
    };

    /// Пусковой контактор фазоращепителя
    Relay *K119 = new Relay(K119_NUM_CONTACTS);

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;

    void stepKeysControl(double t, double dt) override;
};

#endif // PANEL_1_H
