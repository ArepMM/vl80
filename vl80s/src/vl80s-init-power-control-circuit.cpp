#include    <vl80s.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void VL80s::initPowerControlCircuit(const QString &modules_dir,
                                    const QString &custom_cfg_dir)
{
    battery->read_config("battery", custom_cfg_dir);

    shield_215->read_config("shield-215", custom_cfg_dir);

    shield_216->read_config("shield-216", custom_cfg_dir);

    shield_210->read_config("shield-210", custom_cfg_dir);
    shield_210->init(custom_cfg_dir);

    shield_223->read_config("shield-223", custom_cfg_dir);
    shield_223->setAnalogSignalsPtr(&analogSignal);

    shield_224->read_config("shield-224", custom_cfg_dir);
    shield_224->setAnalogSignalsPtr(&analogSignal);

    shield_225->read_config("shield-225", custom_cfg_dir);

    shield_226->read_config("shield-226", custom_cfg_dir);

    shield_227->read_config("shield-227", custom_cfg_dir);

    shield_228->read_config("shield-228", custom_cfg_dir);

    shield_229->read_config("shield-229", custom_cfg_dir);

    // Контроллер машиниста
    km->init(custom_cfg_dir);
    km->read_config("km-84", custom_cfg_dir);
    km->insertReversHandle(revers_handle_init_state);

    panel_1->read_config("panel-1", custom_cfg_dir);
    panel_1->init(custom_cfg_dir);
    panel_1->setAnalogSignalsPtr(&analogSignal);

    panel_2->read_config("panel-2", custom_cfg_dir);
    panel_2->init(custom_cfg_dir);
    panel_2->setAnalogSignalsPtr(&analogSignal);

    panel_3->read_config("panel-3", custom_cfg_dir);
    panel_3->init(custom_cfg_dir);
    panel_3->setAnalogSignalsPtr(&analogSignal);

    panel_4->read_config("panel-4", custom_cfg_dir);
    panel_4->init(custom_cfg_dir);
    panel_4->setAnalogSignalsPtr(&analogSignal);

    panel_5->read_config("panel-5", custom_cfg_dir);
    panel_5->init(custom_cfg_dir);
    panel_5->setAnalogSignalsPtr(&analogSignal);

    panel_6->read_config("panel-6", custom_cfg_dir);
    panel_6->init(custom_cfg_dir);
    panel_6->setAnalogSignalsPtr(&analogSignal);

    panel_7->read_config("panel-7", custom_cfg_dir);
    panel_7->init(custom_cfg_dir);
    panel_7->setAnalogSignalsPtr(&analogSignal);

    panel_8->read_config("panel-8", custom_cfg_dir);
    panel_8->init(custom_cfg_dir);
    panel_8->setAnalogSignalsPtr(&analogSignal);

    panel_9->read_config("panel-9", custom_cfg_dir);
    panel_9->init(custom_cfg_dir);
    panel_9->setAnalogSignalsPtr(&analogSignal);
}
