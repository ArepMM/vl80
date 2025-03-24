#include    <compressor.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Compressor::Compressor(QObject *parent)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Compressor::~Compressor()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Compressor::preStep(state_vector_t &Y, double t)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Compressor::ode_system(const state_vector_t &Y,
                            state_vector_t &dYdt,
                            double t)
{
    // Текущая степень сжатия воздуха
    double ksi = eps / (1 + 0.5 * (eps - 1) * (1 - cos(Y[1]) + lambda - sqrt(lambda * lambda - pow(sin(Y[1]), 2.0))));

    double sin_beta = sin(Y[1]) / lambda;
    double cos_beta = sqrt(1 - sin_beta * sin_beta);

    // Текущее  избыточное давление
    double p = Physics::pA * (pow(ksi, gamma) - 1.0) * hs_p(Y[0]);

    // Момент сопротивления движению
    double Mc = Physics::fricForce(Mxx, 0.1 * Y[0]);

    Q_out = K_flow * pf(p / Physics::MPa - p_out);

    dYdt[0] = (ip * M - Mc) / J;

    dYdt[1] = Y[0];
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Compressor::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    cfg.getDouble(secName, "eps", eps);
    cfg.getDouble(secName, "S", S);
    cfg.getDouble(secName, "h", h);
    cfg.getDouble(secName, "J", J);
    cfg.getDouble(secName, "Mxx", Mxx);
    cfg.getDouble(secName, "ip", ip);
    cfg.getDouble(secName, "K_flow", K_flow);

    setY(0, 0.0);
    setY(1, Physics::PI);
}
