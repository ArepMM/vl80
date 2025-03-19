#include    <shield-210.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Shield_210::Shield_210(size_t input_wires_num,
                       size_t output_wires_num,
                       QObject *parent)
    : ElectricModule(input_wires_num, output_wires_num, parent)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Shield_210::~Shield_210()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_210::init(const QString &custom_cfg_dir)
{
    K->read_config("mk-69", custom_cfg_dir);
    K->setInitContactState(K_9_21, true);
    K->setInitContactState(K_31_32, true);
    K->setInitContactState(K_16_17, true);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_210::step(double t, double dt)
{
    ElectricModule::step(t, dt);

    K->setVoltage(U_rect);
    K->step(t, dt);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_210::preStep(state_vector_t &Y, double t)
{
    // Провод Н116 ("+" АКБ)
    bool is_N116_ON = switch_2R.getState();

    // ЭДС выпрямителя зарядного агрегата
    E_ref = cut( K_u * (U_ref - U_rect), 0.0, K_rect * Uac);

    // Ток, потребляемый нагрузкой
    double I = pf(I_load) + K->getCurrent();

    // Ток потребляемый нагрузкой от батареи
    I_bat = pf(I_load) * static_cast<double>(K->getContactState(K_31_32));

    // Напряжение на выходе выпрямителя зарядного агрегата
    U_rect = pf(Y[0] - r * I);

    output_wire[S210_N116] = U_rect * static_cast<double>(is_N116_ON);

    // Напряжение аккумуляторной батареи
    double U_bat = input_wire[S210_N113];

    // Напряжение на проводе Э61
    double U_E61 = max(U_rect, U_bat * static_cast<double>(K->getContactState(K_31_32)));

    // Признак замыкание аварийной цепи питания секции
    double u_fault = static_cast<double>(switch_3R.getState());

    // Расчет напряжения на выходах щита 210
    output_wire[S210_N0] = U_E61 * (1.0 - u_fault) + input_wire[S210_E62] * u_fault;
    output_wire[S210_N49] = output_wire[S210_N0];
    output_wire[S210_N401] = output_wire[S210_N0];
    output_wire[S210_N402] = output_wire[S210_N0];
    output_wire[S210_N66] = output_wire[S210_N0];

    output_wire[S210_N119] = U_rect * (1.0 - u_fault) + input_wire[S210_E66] * u_fault;

    // Аварийное питание 2 секции
    output_wire[S210_E61] = U_E61;
    output_wire[S210_E65] = U_rect;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_210::ode_system(const state_vector_t &Y,
                            state_vector_t &dYdt,
                            double t)
{
    dYdt[0] = (E_ref - Y[0]) / T_rect;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shield_210::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    bool switch_2R_state = false;
    cfg.getBool(secName, "Switch2R_state", switch_2R_state);

    if (switch_2R_state)
    {
        switch_2R.set();
    }

    bool switch_3R_state = false;
    cfg.getBool(secName, "Switch3R_state", switch_3R_state);

    if (switch_3R_state)
    {
        switch_3R.set();
    }

    cfg.getDouble(secName, "K_u", K_u);
    cfg.getDouble(secName, "T_rect", T_rect);
    cfg.getDouble(secName, "r", r);
    cfg.getDouble(secName, "U_ref", U_ref);
}

void Shield_210::stepKeysControl(double t, double dt)
{

}
