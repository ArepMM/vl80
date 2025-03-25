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

    // TODO // Запреты на включение реверсивки и тумблеров в неактивной кабине

    // TODO // всё остальное взаимодействие секций вл80

    // Управление
    sme_fwd->setControl(keys);
    sme_fwd->step(t, dt);
    sme_bwd->setControl(keys);
    sme_bwd->step(t, dt);
}
