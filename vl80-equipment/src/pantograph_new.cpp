#include    "pantograph_new.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Pantograph_new::Pantograph_new(QObject *parent) : Device(parent)
{
    setY(HEIGHT, height_down);

    name = QString("ks");

    input_signals.resize(SIZE_OF_INPUTS);
    output_signals.resize(SIZE_OF_OUTPUTS);

    output_signals[OUTPUT_CURRENT] = 0.0;
    input_signals[INPUT_WIRE_HEIGHT] = 6.56;
    input_signals[INPUT_VOLTAGE] = 0.0;
    input_signals[INPUT_FREQUENCY] = 0.0;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Pantograph_new::~Pantograph_new()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Pantograph_new::setCurrent(double I)
{
    output_signals[OUTPUT_CURRENT] = I;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Pantograph_new::setPneumodriveRefPressure(double p)
{
    pc = p;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Pantograph_new::setWireHeight(double h)
{
    input_signals[INPUT_WIRE_HEIGHT] = h;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Pantograph_new::setVoltage(double U)
{
    input_signals[INPUT_VOLTAGE] = U;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Pantograph_new::setFrequency(double f)
{
    input_signals[INPUT_FREQUENCY] = f;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double Pantograph_new::getPneumodriveFlow() const
{
    return Qc;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double Pantograph_new::getHeight() const
{
    return getY(HEIGHT);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double Pantograph_new::getRelativeHeight() const
{
    return (getY(HEIGHT) - height_down) / (height_up - height_down);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double Pantograph_new::getVoltage() const
{
    if (is_contact)
        return input_signals[INPUT_VOLTAGE];

    return 0.0;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double Pantograph_new::getFrequency() const
{
    if (is_contact)
        return input_signals[INPUT_FREQUENCY];

    return 0.0;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
sound_state_t Pantograph_new::getSoundState(size_t idx) const
{
    return ref_state.getSoundState(idx);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
float Pantograph_new::getSoundSignal(size_t idx) const
{
    return ref_state.getSoundSignal(idx);
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void Pantograph_new::ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t)
{
    (void) t;

    // Давление в пневмоприводе
    Qc = (Y[PRESSURE] - pc) * Kc;
    dYdt[PRESSURE] = -Qc / Vc;

    // Высота токоприёмника
    if (Y[PRESSURE] > Pmin)
    {
        // Поднятие токоприёмника
        // Скорость поднятия с учётом давления в пневмоприводе, м/с
        double motion_v = motion_v_nom * ((Y[PRESSURE] - Pmin) / (Pnom - Pmin));

        // Целевая высота полоза - высота контактного провода
        double ref_height = input_signals[INPUT_WIRE_HEIGHT];

        // Проверяем, что есть контактный провод, и его высота
        // не выше максимально поднятого полоза и не ниже опущенного
        if ( is_linked &&
            ( (ref_height < height_up) ||
             ((ref_height - height_down) > Physics::ZERO) ) )
        {
            // Проверяем касание полоза и контактного провода
            is_contact = (abs(Y[HEIGHT] - ref_height) < eps);
        }
        else
        {
            // Если провода нет, поднимаем без ограничения
            ref_height = height_up;

            // Отключаем токоприёмник
            is_contact = false;
        }

        // Расстояние до целевой высоты
        double height_delta = ref_height - Y[HEIGHT];

        // Токоприёмник стремится к проводу
        dYdt[HEIGHT] = motion_v * (cut(height_delta, -eps, eps) / eps);

        // Озвучка // TODO // Переделать
        ref_state.set();
    }
    else
    {
        // Опускание токоприёмника
        // Скорость опускания токоприёмника с учётом давления в пневмоприводе, м/с
        double motion_v = motion_v_nom * ((Pmin - Y[PRESSURE]) / Pmin);

        // Отключаем токоприёмник
        is_contact = false;

        // Расстояние до опущенного состояния
        double height_delta = Y[HEIGHT] - height_down;

        // Токоприёмник стремится опустится
        dYdt[HEIGHT] = -1.0 * motion_v * (min(height_delta, eps) / eps);

        // Озвучка // TODO // Переделать
        ref_state.reset();
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Pantograph_new::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    double tmp = 0.0;
    cfg.getDouble(secName, "Vc", tmp);
    if (tmp > 1e-3)
        Vc = tmp;

    cfg.getDouble(secName, "Kc", Kc);
    cfg.getDouble(secName, "Pmin", Pmin);
    cfg.getDouble(secName, "Pnom", Pnom);
    cfg.getDouble(secName, "MotionTime", motion_time);
    cfg.getDouble(secName, "HeightDown", height_down);
    cfg.getDouble(secName, "HeightUp", height_up);

    setY(HEIGHT, height_down);
}
