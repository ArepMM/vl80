#include    "vl80s.h"

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
void VL80s::initBrakeDevices(double p0, double pBP, double pFL)
{
    // Инициализация давления в питательной магистрали
    main_reservoir->setY(0, pFL);
    anglecock_fl_fwd->setPipePressure(pFL);
    anglecock_fl_bwd->setPipePressure(pFL);
    hose_fl_fwd->setPressure(pFL);
    hose_fl_bwd->setPressure(pFL);

    // Состояние рукавов и концевых кранов питательной магистрали
    if (hose_fl_fwd->isLinked())
    {
        hose_fl_fwd->connect();
        anglecock_fl_fwd->open();
    }
    else
    {
        anglecock_fl_fwd->close();
    }

    if (hose_fl_bwd->isLinked())
    {
        hose_fl_bwd->connect();
        anglecock_fl_bwd->open();
    }
    else
    {
        anglecock_fl_bwd->close();
    }
}
