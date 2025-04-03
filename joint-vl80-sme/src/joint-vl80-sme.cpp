#include    "joint-vl80-sme.h"

#include    "vl80-sme-signals.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
JointVL80sme::JointVL80sme() : Joint()
  , is_connected(false)
{
    devices.resize(NUM_CONNECTORS);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
JointVL80sme::~JointVL80sme()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void JointVL80sme::step(double t, double dt)
{
    Q_UNUSED(t)
    Q_UNUSED(dt)

    // Управление соединением СМЕ, если не более 4 секций
    if (((devices[FWD]->getOutputSignal(SME_OUTPUT_REF_STATE) == 1.0) ||
        (devices[BWD]->getOutputSignal(SME_OUTPUT_REF_STATE) == 1.0)) &&
        ((devices[FWD]->getOutputSignal(SME_NUM_SECTIONS) +
        (devices[BWD]->getOutputSignal(SME_NUM_SECTIONS))) <= 4.0))
    {
        is_connected = true;
    }

    // Управление разъединением СМЕ, либо обнаружение уже 4 секций
    if ((devices[FWD]->getOutputSignal(SME_OUTPUT_REF_STATE) == -1.0) ||
        (devices[BWD]->getOutputSignal(SME_OUTPUT_REF_STATE) == -1.0) ||
        (devices[FWD]->getOutputSignal(SME_NUM_SECTIONS) >= 4.0) ||
        (devices[BWD]->getOutputSignal(SME_NUM_SECTIONS) >= 4.0))
    {
        is_connected = false;
    }

    if (is_connected)
    {
        devices[FWD]->setInputSignal(SME_INPUT_IS_CONNECTED, 1.0);
        devices[BWD]->setInputSignal(SME_INPUT_IS_CONNECTED, 1.0);

        // Сигнал-счётчик количества соединённых в СМЕ секций
        devices[FWD]->setInputSignal(SME_NUM_SECTIONS, devices[BWD]->getOutputSignal(SME_NUM_SECTIONS));
        devices[BWD]->setInputSignal(SME_NUM_SECTIONS, devices[FWD]->getOutputSignal(SME_NUM_SECTIONS));

        // Сигнал запрета вставлять реверсивную рукоятку в других кабинах
        devices[FWD]->setInputSignal(SME_NO_REVERS_HANDLE, devices[BWD]->getOutputSignal(SME_NO_REVERS_HANDLE));
        devices[BWD]->setInputSignal(SME_NO_REVERS_HANDLE, devices[FWD]->getOutputSignal(SME_NO_REVERS_HANDLE));

        // Сигнал запрета разблокировать УБТ в других кабинах
        devices[FWD]->setInputSignal(SME_NO_BRAKELOCK_KEY, devices[BWD]->getOutputSignal(SME_NO_BRAKELOCK_KEY));
        devices[BWD]->setInputSignal(SME_NO_BRAKELOCK_KEY, devices[FWD]->getOutputSignal(SME_NO_BRAKELOCK_KEY));

        // Цепи управления токоприемниками
        devices[FWD]->setInputSignal(SME_E15_IN, devices[BWD]->getOutputSignal(SME_E15_OUT));
        devices[BWD]->setInputSignal(SME_E15_IN, devices[FWD]->getOutputSignal(SME_E15_OUT));

        devices[FWD]->setInputSignal(SME_E16_IN, devices[BWD]->getOutputSignal(SME_E17_OUT));
        devices[BWD]->setInputSignal(SME_E16_IN, devices[FWD]->getOutputSignal(SME_E17_OUT));

        devices[FWD]->setInputSignal(SME_E17_IN, devices[BWD]->getOutputSignal(SME_E16_OUT));
        devices[BWD]->setInputSignal(SME_E17_IN, devices[FWD]->getOutputSignal(SME_E16_OUT));

        devices[FWD]->setInputSignal(SME_E35_IN, devices[BWD]->getOutputSignal(SME_E35_OUT));
        devices[BWD]->setInputSignal(SME_E35_IN, devices[FWD]->getOutputSignal(SME_E35_OUT));

        devices[FWD]->setInputSignal(SME_E27_IN, devices[BWD]->getOutputSignal(SME_E28_OUT));
        devices[BWD]->setInputSignal(SME_E27_IN, devices[FWD]->getOutputSignal(SME_E28_OUT));

        devices[FWD]->setInputSignal(SME_E28_IN, devices[BWD]->getOutputSignal(SME_E27_OUT));
        devices[BWD]->setInputSignal(SME_E28_IN, devices[FWD]->getOutputSignal(SME_E27_OUT));

        devices[FWD]->setInputSignal(SME_E37_IN, devices[BWD]->getOutputSignal(SME_E37_OUT));
        devices[BWD]->setInputSignal(SME_E37_IN, devices[FWD]->getOutputSignal(SME_E37_OUT));

        devices[FWD]->setInputSignal(SME_E30_IN, devices[BWD]->getOutputSignal(SME_E30_OUT));
        devices[BWD]->setInputSignal(SME_E30_IN, devices[FWD]->getOutputSignal(SME_E30_OUT));
    }
    else
    {
        devices[FWD]->setInputSignal(SME_INPUT_IS_CONNECTED, 0.0);
        devices[BWD]->setInputSignal(SME_INPUT_IS_CONNECTED, 0.0);

        // Несоединённые контакты СМЕ
        for (size_t i = SME_NUM_SECTIONS; i < NUM_VL80_SME_SIGNALS; ++i)
        {
            devices[FWD]->setInputSignal(i, 0.0);
            devices[BWD]->setInputSignal(i, 0.0);
        }
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void JointVL80sme::load_config(CfgReader &cfg)
{
    QString secName = "Joint";
    cfg.getBool(secName, "initConnectionState", is_connected);
}

GET_JOINT(JointVL80sme)
