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

    void init(const QString &custom_cfg_dir);

    enum P1_InputWires
    {
        INPUTS_NUM = 1
    };

    enum P1_OutputWires
    {
        OUTPUTS_NUM = 1
    };

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

    /// Контакты К113
    enum
    {
        K113_NUM_CONTACTS = 1,
        K113_N75_N76 = 0,
    };

    /// Реле перегрузки вспомогательных цепей
    Relay *K113 = new Relay(K113_NUM_CONTACTS);

    /// Контакты К125
    enum
    {
        K125_NUM_CONTACTS = 4,
        K125_N471_N404 = 0,
        K125_N179_N170 = 1,
        K125_N100_Э18 = 2,
        K125_N103_NТ107 = 3
    };

    /// Фазоращепитель
    Relay *K125 = new Relay(K125_NUM_CONTACTS);

    /// Контакты К124
    enum
    {
        K124_NUM_CONTACTS = 2,
        K124_N010_N146 = 0,
        K124_N106_N110 = 1
    };

    /// Компрессор
    Relay *K124 = new Relay(K124_NUM_CONTACTS);

    /// Контакты К127
    enum
    {
        K127_NUM_CONTACTS = 3,
        K127_N475_N404 = 0,
        K127_N104_N490 = 1,
        K127_N467_N010 = 2
    };

    /// Вентилятор 1
    Relay *K127 = new Relay(K127_NUM_CONTACTS);

    /// Контакты К128
    enum
    {
        K128_NUM_CONTACTS = 4,
        K128_N477_N404 = 0,
        K128_N490_N104 = 1,
        K128_N010_N468 = 2,
        K128_N359_N363 = 3
    };

    /// Вентилятор 2
    Relay *K128 = new Relay(K128_NUM_CONTACTS);

    /// Контакты К129
    enum
    {
        K129_NUM_CONTACTS = 4,
        K129_N479_N403 = 0,
        K129_N496_N010 = 1,
        K129_N439_N495 = 2,
        K129_N13_N15 = 3
    };

    /// Вентилятор 3
    Relay *K129 = new Relay(K129_NUM_CONTACTS);

    /// Контакты К130
    enum
    {
        K130_NUM_CONTACTS = 4,
        K130_N481_N403 = 0,
        K130_N010_N470 = 1,
        K130_N495_N439 = 2,
        K130_N14_N16 = 3
    };

    /// Вентилятор 4
    Relay *K130 = new Relay(K130_NUM_CONTACTS);

    void preStep(state_vector_t &Y, double t) override;

    void ode_system(const state_vector_t &Y,
                    state_vector_t &dYdt,
                    double t) override;

    void load_config(CfgReader &cfg) override;

    void stepKeysControl(double t, double dt) override;
};

#endif // PANEL_1_H
