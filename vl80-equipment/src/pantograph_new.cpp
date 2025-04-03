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

    // Целевая высота полоза токоприёмника - высота контактного провода
    double ref_height = input_signals[INPUT_WIRE_HEIGHT];

    // Если нет контактного провода, или его высота
    // выше максимально поднятого полоза или ниже опущенного
    if ((!is_linked) ||
        (ref_height > height_up) ||
        ( (ref_height - height_down) < Physics::ZERO ))
    {
        // Если провода нет, отключаем токоприёмник
        is_contact = false;

        // Проверяем давление в пневмоприводе
        if (Y[PRESSURE] > Pmin)
        {
            // Озвучка // TODO // Переделать
            ref_state.set();

            // Давление поднимает полоз без ограничения до макисмальной высоты
            if (Y[HEIGHT] < height_up)
            {
                // Скорость поднятия с учётом давления в пневмоприводе, м/с
                dYdt[HEIGHT] = motion_v_nom * ((Y[PRESSURE] - Pmin) / (Pnom - Pmin));
                return;
            }

            // Не позволяем подниматься выше максимума
            dYdt[HEIGHT] = 0.0;
            if (Y[HEIGHT] - height_up > Physics::ZERO)
            {
                setY(HEIGHT, ref_height);
            }
            return;
        }
    }
    else
    {
        // Провод всегда прижимает токоприёмник вниз
        if (Y[HEIGHT] - ref_height > Physics::ZERO)
        {
            setY(HEIGHT, ref_height);
            dYdt[HEIGHT] = 0.0;
            is_contact = true;
            return;
        }

        // Проверяем касание полоза и контактного провода
        is_contact = (abs(Y[HEIGHT] - ref_height) < eps);

        // Проверяем давление в пневмоприводе
        if (Y[PRESSURE] > Pmin)
        {
            // Озвучка // TODO // Переделать
            ref_state.set();

            // Давление поднимает полоз к проводу
            if (Y[HEIGHT] < ref_height)
            {
                // Скорость поднятия с учётом давления в пневмоприводе, м/с
                dYdt[HEIGHT] = motion_v_nom * ((Y[PRESSURE] - Pmin) / (Pnom - Pmin));
                return;
            }

            // Не позволяем подниматься выше провода
            dYdt[HEIGHT] = 0.0;
            return;
        }
    }

    // Сюда программа доходит в случае давления в пневмоприводе ниже минимального
    // Озвучка // TODO // Переделать
    ref_state.reset();

    // Скорость опускания токоприёмника с учётом давления в пневмоприводе, м/с
    double motion_v = motion_v_nom * ((Pmin - Y[PRESSURE]) / Pmin);

    // Расстояние до опущенного состояния
    double height_delta = Y[HEIGHT] - height_down;

    // Токоприёмник стремится опуститься, но в конце мягко сложиться
    dYdt[HEIGHT] = -1.0 * motion_v * (min(height_delta, eps) / eps);
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

    motion_v_nom = (height_up - height_down) / motion_time;
    setY(HEIGHT, height_down);
}
