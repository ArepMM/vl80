#include    <dc-motor.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
DCMotor::DCMotor(QObject *parent)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
DCMotor::~DCMotor()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void DCMotor::preStep(state_vector_t &Y, double t)
{
    if (field_mode == SERIES)
    {
        Y[1] = Y[0] * beta;
    }

    M = Y[0] * cPhi(Y[1]);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void DCMotor::ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t)
{
    switch (field_mode)
    {
    case SERIES:
        {
            double R = Ra + beta * Rf;

            dYdt[0] = (Ua - R * Y[0] - omega * cPhi(beta * Y[0])) / (Ta * Ra + Tf * Rf);

            dYdt[1] = 0.0;

            break;
        }

    case PARALLEL:
        {
            dYdt[0] = (Ua - Ra * Y[0] - omega * cPhi(Y[1])) / Ta / Ra;

            dYdt[1] = (Ua - Rf * Y[1]) / Tf / Rf;

            break;
        }

    case INDEPENDENT:
        {
            dYdt[0] = (Ua - Ra * Y[0] - omega * cPhi(Y[1])) / Ta / Ra;

            dYdt[1] = (Uf - Rf * Y[1]) / Tf / Rf;

            break;
        }
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void DCMotor::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    cfg.getDouble(secName, "Ra", Ra);
    cfg.getDouble(secName, "Rf", Rf);
    cfg.getDouble(secName, "Ta", Ta);
    cfg.getDouble(secName, "Tf", Tf);
    cfg.getDouble(secName, "cPhi_nom", cPhi_nom);
    cfg.getDouble(secName, "Unom", Unom);
    cfg.getDouble(secName, "Inom", Inom);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double DCMotor::cPhi(double If)
{
    double cPhi = 0.0;

    for (size_t i = 0; i < a.size(); ++i)
    {
        double b_i = cPhi_nom * a[i] / pow(Inom, i+1);

        cPhi += b_i * pow(If, i+1);
    }

    return cPhi;
}
