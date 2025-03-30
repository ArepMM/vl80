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

    // Инициализация давления в приборах управления тормозами
    brake_crane->setChargePressure(p0);
    brake_crane->init(pBP, pFL);
    loco_crane->init(pBP, pFL);

    // Инициализация давления в тормозной магистрали
    brakepipe->setY(0, pBP);
    anglecock_bp_fwd->setPipePressure(pBP);
    anglecock_bp_bwd->setPipePressure(pBP);
    hose_bp_fwd->setPressure(pBP);
    hose_bp_bwd->setPressure(pBP);

    air_dist->init(pBP, pFL);

    supply_reservoir->setY(0, pBP);

    // Инициализация давлений в резервуарах токоприемника и ГВ
    switch_reservoir->setY(0, pFL);
    pant_reservoir->setY(0, min(0.5, pFL));

    // Состояние рукава и концевого крана импульсной магистрали сзади
    if (hose_il_bwd->isLinked())
    {
        hose_il_bwd->connect();
        anglecock_il_bwd->open();
    }
    else
    {
        anglecock_il_bwd->close();
    }

    // Состояние рукавов и концевых кранов магистрали тормозных цилиндров
    if (hose_bc_fwd->isLinked())
    {
        hose_bc_fwd->connect();
        anglecock_bc_fwd->open();
    }
    else
    {
        anglecock_bc_fwd->close();
    }

    if (hose_bc_bwd->isLinked())
    {
        hose_bc_bwd->connect();
        anglecock_bc_bwd->open();
    }
    else
    {
        anglecock_bc_bwd->close();
    }

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

    // Состояние рукавов и концевых кранов тормозной магистрали
    if (hose_bp_fwd->isLinked())
    {
        hose_bp_fwd->connect();
        anglecock_bp_fwd->open();
    }
    else
    {
        anglecock_bp_fwd->close();
    }

    if (hose_bp_bwd->isLinked())
    {
        hose_bp_bwd->connect();
        anglecock_bp_bwd->open();
    }
    else
    {
        anglecock_bp_bwd->close();
    }
}
