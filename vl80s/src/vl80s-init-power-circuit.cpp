#include    <vl80s.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void VL80s::initPowerCircuit(const QString &modules_dir,
                             const QString &custom_cfg_dir)
{
    // Пантограф
    pantograph->read_config("pantograph", custom_cfg_dir);
    // TODO // Заготовка под энергоснабжение с инфраструктуры маршрута
    addRailwayConnector(pantograph, 4.6);
}
