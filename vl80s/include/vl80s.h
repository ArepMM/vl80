#ifndef		VL80S_H
#define		VL80S_H

#include    <vehicle-api.h>
#include    <km-84.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class VL80s : public Vehicle
{
public:

    VL80s(QObject *parent = Q_NULLPTR);

    ~VL80s();

private:

    ControllerKM84 *km = new ControllerKM84;
};

#endif // VL80S_H
