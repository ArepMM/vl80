#ifndef     JOINT_VL80_SME_H
#define     JOINT_VL80_SME_H

#include    "device-joint.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class JointVL80sme : public Joint
{
public:

    /// Конструктор
    JointVL80sme();

    /// Деструктор
    ~JointVL80sme();

    /// Шаг симуляции
    void step(double t, double dt);

private:

    enum
    {
        NUM_CONNECTORS = 2,
        FWD = 0,
        BWD = 1
    };

    /// Состояние межсекционного соединения
    bool is_connected;

    /// Загрузка параметров из конфига
    void load_config(CfgReader &cfg);
};

#endif // JOINT_VL80_SME_H
