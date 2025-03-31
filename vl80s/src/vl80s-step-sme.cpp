#include    <vl80s.h>
#include    <vl80-sme-signals.h>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void VL80s::stepSME(double t, double dt)
{
    // Опрос количества секций в СМЕ
    sme_fwd->setSignal(SME_NUM_SECTIONS, sme_bwd->getSignal(SME_NUM_SECTIONS) + 1.0);
    sme_bwd->setSignal(SME_NUM_SECTIONS, sme_fwd->getSignal(SME_NUM_SECTIONS) + 1.0);

    if (km->isReversHandle())
    {
        // Запрет на включение реверсивки в других кабинах
        sme_fwd->setSignal(SME_NO_REVERS_HANDLE, 1.0);
        sme_bwd->setSignal(SME_NO_REVERS_HANDLE, 1.0);
    }
    else
    {
        // Пропускаем дальше запрет на включение реверсивки в других кабинах
        sme_fwd->setSignal(SME_NO_REVERS_HANDLE, sme_bwd->getSignal(SME_NO_REVERS_HANDLE));
        sme_bwd->setSignal(SME_NO_REVERS_HANDLE, sme_fwd->getSignal(SME_NO_REVERS_HANDLE));
    }

    // TODO // Добавить в движке возможность вставить / снять рукоятку УБТ
    // TODO // и сделать аналогичный запрет включать УБТ в других кабинах

    // TODO // всё остальное взаимодействие секций вл80
    sme_bwd->setSignal(SME_E15_OUT, shield_223->getOutputVoltage(Shield_223::E15));

    // Управление
    sme_fwd->setControl(keys);
    sme_fwd->step(t, dt);
    sme_bwd->setControl(keys);
    sme_bwd->step(t, dt);
}
