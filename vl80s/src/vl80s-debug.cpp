#include    "vl80s.h"

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
void VL80s::stepDebugPrint(double t, double dt)
{
    (void) t;
    (void) dt;

    DebugMsg = "";
    DebugMsg += QString("x%1 km|V%2 km/h|")
                    .arg(profile_point_data.railway_coord / 1000.0, 10, 'f', 3)
                    .arg(velocity * Physics::kmh, 6, 'f', 1);
    DebugMsg += QString("pBP%1|pIL%2|pBCf%3|pBCb%4|pSR%5|")
                    .arg(10.0 * brakepipe->getPressure(), 6, 'f', 2)
                    .arg(10.0 * impulse_line->getPressure(), 6, 'f', 2)
                    .arg(10.0 * brake_mech[TROLLEY_FWD]->getBCpressure(), 6, 'f', 2)
                    .arg(10.0 * brake_mech[TROLLEY_BWD]->getBCpressure(), 6, 'f', 2)
                    .arg(10.0 * supply_reservoir->getPressure(), 6, 'f', 2);
    DebugMsg += QString("pFL%1|pER%2|395:%3|254:%4%|")
                    .arg(10.0 * main_reservoir->getPressure(), 6, 'f', 2)
                    .arg(10.0 * brake_crane->getERpressure(), 6, 'f', 2)
                    .arg(brake_crane->getPositionName(), 3)
                    .arg(loco_crane->getHandlePosition() * 100.0, 3, 'f', 0);

    DebugMsg += QString("\n");

    DebugMsg += QString("%1%2%3-%4-couplings-%5-%6%7%8")
                    .arg(coupling_fwd->isLinked() ? "=" : " ")
                    .arg(coupling_fwd->isCoupled() ? "=" : " ")
                    .arg((coupling_fwd->getOutputSignal(COUPL_OUTPUT_REF_STATE) > -0.5) ? "=" : ">")
                    .arg((oper_rod_fwd->getOperatingState() > -0.5) ? "|" : "/")
                    .arg((oper_rod_bwd->getOperatingState() > -0.5) ? "|" : "\\")
                    .arg((coupling_bwd->getOutputSignal(COUPL_OUTPUT_REF_STATE) > -0.5) ? "=" : "<")
                    .arg(coupling_bwd->isCoupled() ? "=" : " ")
                    .arg(coupling_bwd->isLinked() ? "=" : " ");
    DebugMsg += QString("  |  ");
    DebugMsg += QString("%1%2/=%3==BP==%4=\\%5%6")
                    .arg(hose_bp_fwd->isLinked() ? "\\" : " ")
                    .arg(hose_bp_fwd->isConnected() ? "_" : " ")
                    .arg(anglecock_bp_fwd->isOpened() ? "/" : "|")
                    .arg(anglecock_bp_bwd->isOpened() ? "\\" : "|")
                    .arg(hose_bp_bwd->isConnected() ? "_" : " ")
                    .arg(hose_bp_bwd->isLinked() ? "/" : " ");
    DebugMsg += QString("  |  ");
    DebugMsg += QString("%1%2/=%3==FL==%4=\\%5%6")
                    .arg(hose_fl_fwd->isLinked() ? "\\" : " ")
                    .arg(hose_fl_fwd->isConnected() ? "_" : " ")
                    .arg(anglecock_fl_fwd->isOpened() ? "/" : "|")
                    .arg(anglecock_fl_bwd->isOpened() ? "\\" : "|")
                    .arg(hose_fl_bwd->isConnected() ? "_" : " ")
                    .arg(hose_fl_bwd->isLinked() ? "/" : " ");
    DebugMsg += QString("  |  ");
    DebugMsg += QString("%1%2/=%3==BC==%4=\\%5%6")
                    .arg(hose_bc_fwd->isLinked() ? "\\" : " ")
                    .arg(hose_bc_fwd->isConnected() ? "_" : " ")
                    .arg(anglecock_bc_fwd->isOpened() ? "/" : "|")
                    .arg(anglecock_bc_bwd->isOpened() ? "\\" : "|")
                    .arg(hose_bc_bwd->isConnected() ? "_" : " ")
                    .arg(hose_bc_bwd->isLinked() ? "/" : " ");
    DebugMsg += QString("  |  ");
    DebugMsg += QString("|==IL==%1=\\%2%3")
                    .arg(anglecock_il_bwd->isOpened() ? "\\" : "|")
                    .arg(hose_il_bwd->isConnected() ? "_" : " ")
                    .arg(hose_il_bwd->isLinked() ? "/" : " ");
    DebugMsg += QString("  |  ");
    DebugMsg += QString("%1%2=-SME-=%3%4")
                    .arg(sme_fwd->isLinked() ? "=" : " ")
                    .arg(sme_fwd->isConnected() ? "=" : " ")
                    .arg(sme_bwd->isConnected() ? "=" : " ")
                    .arg(sme_bwd->isLinked() ? "=" : " ");

    DebugMsg += QString("  |  ");
    DebugMsg += QString("BP=%1=AD=%2=IL")
                    .arg(shutoff_ad_bp->isOpened() ? "=" : "|")
                    .arg(shutoff_ad_il->isOpened() ? "=" : "|");

    DebugMsg += QString("\n");

    DebugMsg += QString("Реверсивка: %1 | Валы КМ: Реверс %2 | Глав. %3 | Торм. %4 (Угол: %5)")
                    .arg(km->isReversHandle())
                    .arg(km->getReversPosName(), 3)
                    .arg(km->getMainPosName(), 3)
                    .arg(km->getBrakePosName(), 3)
                    .arg(km->getBrakeShaftAngle(), 5, 'f', 0);

    DebugMsg += QString("\n");

    DebugMsg += QString("Всп. компр.: %1 об/мин | Q: %2 | Рез. ТП.: %3 кгс/см2 | Рез. ГВ.: %4 кгс/см2")
                    .arg(aux_compr->getOmega() * 30.0 / Physics::PI, 7, 'f', 2)
                    .arg(aux_compr->getQ_out(), 4, 'f', 2)
                    .arg(pant_res->getPressure() * Physics::g, 4, 'f', 2)
                    .arg(main_switch_res->getPressure() * Physics::g, 4, 'f', 2);
/*
    DebugMsg += QString("\n");
    DebugMsg += QString("FWD Speed limit %1 km/h | Next %2 km/h (%3 m)")
                    .arg(speedmap_fwd->getCurrentLimit(), 3, 'f', 0)
                    .arg(speedmap_fwd->getNextLimit(), 3, 'f', 0)
                    .arg(speedmap_fwd->getNextLimitDistance(), 6, 'f', 1);
    DebugMsg += QString("  |  ");
    DebugMsg += QString("FWD Signal code %1 (%2 Hz) | Next %3 (%4 m)")
                    .arg(coil_ALSN_fwd->getCode(), 1)
                    .arg(coil_ALSN_fwd->getFrequency(), 3, 'f', 0)
                    .arg(coil_ALSN_fwd->getNextSignalLiter())
                    .arg(coil_ALSN_fwd->getNextSignalDistance(), 6, 'f', 1);
*/
}
