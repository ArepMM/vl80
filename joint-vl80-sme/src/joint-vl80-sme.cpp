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

        for (size_t i = SME_NUM_SECTIONS; i < NUM_VL80_SME_SIGNALS; ++i)
        {
            devices[FWD]->setInputSignal(i, devices[BWD]->getOutputSignal(i));
            devices[BWD]->setInputSignal(i, devices[FWD]->getOutputSignal(i));
        }

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
