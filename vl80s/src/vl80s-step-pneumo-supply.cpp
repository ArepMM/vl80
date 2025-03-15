#include    "vl80s.h"

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
void VL80s::stepPneumoSupply(double t, double dt)
{
    // Питательная магистраль
    double FL_flow = 0.0;
    main_reservoir->setFlow(FL_flow);
    main_reservoir->step(t, dt);
}
