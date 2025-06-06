//
// Generated by dtk
// Translation Unit: d_a_arrow_lighteff.cpp
//

#include "d/actor/d_a_arrow_lighteff.h"
#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_arrow.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_graphic.h"
#include "SSystem/SComponent/c_lib.h"

/* 00000078-00000108       .text setTopPos__18daArrow_Lighteff_cFv */
void daArrow_Lighteff_c::setTopPos() {
    daArrow_c* arrow = static_cast<daArrow_c*>(fopAcM_SearchByID(parentActorID));
    if(arrow) {
        mDoMtx_stack_c::copy(arrow->field_0x6b4);
        mDoMtx_stack_c::transM(0.0f, 0.0f, 62.0f);
        mDoMtx_stack_c::multVecZero(&field_0x29C);
    }
}

/* 00000108-00000230       .text setPointLight__18daArrow_Lighteff_cFv */
void daArrow_Lighteff_c::setPointLight() {
    static const s16 light_color[][3] = {
        {0x0000, 0x0000, 0x0000},
        {0x0258, 0x0190, 0x0078},
        {0x0078, 0x0190, 0x0258},
        {0x0258, 0x0258, 0x00C8},
    };

    if(field_0x2EC == 0 || field_0x2EC == 1) {
        if(field_0x2E8 == 0) {
            field_0x33C = 0.0f;
        }
        else {
            cLib_addCalc2(&field_0x33C, cM_rndF(0.2f) + 1.0f, 0.5f, 0.05f);
        }
    }
    else {
        field_0x33C = 0.0f;
    }

    field_0x31C.mPos = field_0x29C;
    field_0x31C.mColor.r = light_color[field_0x2E8][0];
    field_0x31C.mColor.g = light_color[field_0x2E8][1];
    field_0x31C.mColor.b = light_color[field_0x2E8][2];
    field_0x31C.mPower = (s16)(field_0x33C * 150.0f);
    field_0x31C.mFluctuation = 250.0f;
}

/* 00000230-000002C0       .text delete_particle__18daArrow_Lighteff_cFv */
void daArrow_Lighteff_c::delete_particle() {
    if(field_0x2F4.getEmitter()) {
        if(field_0x2E8 == 3) {
            field_0x2F4.getEmitter()->setGlobalAlpha(0);
        }

        field_0x2F4.remove();
    }
    if(field_0x308.getEmitter()) {
        if(field_0x2E8 == 3) {
            field_0x308.getEmitter()->setGlobalAlpha(0);
        }

        field_0x308.remove();
    }
}

/* 000002C0-000002E0       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daArrow_Lighteff_c*>(i_this)->CreateHeap();
}

/* 000002E0-00000624       .text CreateHeap__18daArrow_Lighteff_cFv */
BOOL daArrow_Lighteff_c::CreateHeap() {
    field_0x2E8 = fopAcM_GetParam(this);
    
    J3DModelData* modelData;
    if(field_0x2E8 == 1) {
        modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes("Link", LINK_BDL_GARWFI00));
    }
    else if(field_0x2E8 == 2) {
        modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes("Link", LINK_BDL_GARWFI01));
    }
    else {
        modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes("Link", LINK_BDL_GARWG00));
    }

    JUT_ASSERT(187, modelData != NULL);

    field_0x298 = mDoExt_J3DModel__create(modelData, 0x80000, 0x3F441422);
    if(field_0x298 == 0) {
        return false;
    }

    J3DAnmTextureSRTKey* btk;
    J3DAnmTevRegKey* brk;
    if(field_0x2E8 == 1) {
        btk = static_cast<J3DAnmTextureSRTKey*>(dComIfG_getObjectRes("Link", LINK_BTK_GARWFI00));
        brk = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes("Link", LINK_BRK_GARWFI00));
    }
    else if(field_0x2E8 == 2) {
        btk = static_cast<J3DAnmTextureSRTKey*>(dComIfG_getObjectRes("Link", LINK_BTK_GARWFI01));
        brk = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes("Link", LINK_BRK_GARWFI01));
    }
    else {
        btk = static_cast<J3DAnmTextureSRTKey*>(dComIfG_getObjectRes("Link", LINK_BTK_GARWG00));
        brk = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes("Link", LINK_BRK_GARWG00));
    }

    JUT_ASSERT(216, btk != NULL);
    JUT_ASSERT(217, brk != NULL);

    if(!mBtk.init(modelData, btk, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0)) {
        return false;
    }
    if(!mBrk.init(modelData, brk, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0)) {
        return false;
    }

    field_0x2E0 = 0.0f;

    return true;
}

/* 00000624-00000880       .text CreateInit__18daArrow_Lighteff_cFv */
void daArrow_Lighteff_c::CreateInit() {
    fopAcM_SetMtx(this, field_0x298->getBaseTRMtx());

    field_0x2A8.setall(1.0f);

    fopAcM_setCullSizeBox(this, -100.0f, -100.0f, -100.0f, 100.0f, 100.0f, 100.0f);
    fopAcM_setCullSizeFar(this, 1.0f);

    set_mtx();

    field_0x2E4 = 0;
    field_0x2F0 = 0;
    field_0x2EC = 0;

    setTopPos();

    if(field_0x2E8 == 1) {
        if(field_0x2F4.getEmitter() == 0) {
            dComIfGp_particle_setP1(dPa_name::ID_COMMON_0299, &field_0x29C, &current.angle, NULL, 0xFF, &field_0x2F4);
        }
    }
    else if(field_0x2E8 == 2) {
        if(field_0x2F4.getEmitter() == 0) {
            dComIfGp_particle_setP1(dPa_name::ID_COMMON_029C, &field_0x29C, &current.angle, NULL, 0xFF, &field_0x2F4);
        }
        if(field_0x308.getEmitter() == 0) {
            dComIfGp_particle_setP1(dPa_name::ID_COMMON_029D, &field_0x29C, &current.angle, NULL, 0xFF, &field_0x308);
        }
    }
    else if(field_0x2E8 == 3) {
        if(field_0x2F4.getEmitter() == 0) {
            dComIfGp_particle_setP1(dPa_name::ID_COMMON_029F, &field_0x29C, &current.angle, NULL, 0xFF, &field_0x2F4);
        }
        if(field_0x308.getEmitter() == 0) {
            dComIfGp_particle_setP1(dPa_name::ID_COMMON_02A0, &field_0x29C, &current.angle, NULL, 0xFF, &field_0x308);
        }
    }

    field_0x2E9 = 1;
    dKy_plight_set(&field_0x31C);
}

/* 00000880-00000980       .text set_mtx__18daArrow_Lighteff_cFv */
void daArrow_Lighteff_c::set_mtx() {
    field_0x298->setBaseScale(field_0x2A8);

    daArrow_c* arrow = static_cast<daArrow_c*>(fopAcM_SearchByID(parentActorID));
    if(arrow) {
        mDoMtx_stack_c::copy(arrow->field_0x6b4);
        mDoMtx_stack_c::transM(0.0f, 0.0f, 62.0f);
        field_0x298->setBaseTRMtx(mDoMtx_stack_c::get());
    }
    else {
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::ZXYrotM(current.angle.x, current.angle.y, 0);
        mDoMtx_stack_c::transM(0.0f, 0.0f, 62.0f);
        field_0x298->setBaseTRMtx(mDoMtx_stack_c::get());
    }
}

cPhs_State daArrow_Lighteff_c::_create() {
    fopAcM_SetupActor(this, daArrow_Lighteff_c);

    field_0x2EA = 0;
    if(!fopAcM_entrySolidHeap(this, &CheckCreateHeap, 0x2660)) {
        return cPhs_ERROR_e;
    }

    CreateInit();

    return cPhs_COMPLEATE_e;
}

/* 00000980-00000A70       .text daArrow_Lighteff_Create__FPv */
static cPhs_State daArrow_Lighteff_Create(void* i_this) {
    return static_cast<daArrow_Lighteff_c*>(i_this)->_create();
}

bool daArrow_Lighteff_c::_delete() {
    delete_particle();

    if(field_0x2EA == 1) {
        daPy_py_c* link = daPy_getPlayerActorClass();

        daArrow_c* arrow = static_cast<daArrow_c*>(fopAcM_SearchByID(parentActorID));
        if(arrow) {
            if(!arrow->isSetByZelda()) {
                link->offUseArrowEffect();
            }
        }
        else {
            link->offUseArrowEffect();
        }
    }

    dKy_plight_cut(&field_0x31C);

    return true;
}

/* 00000B70-00000C10       .text daArrow_Lighteff_Delete__FPv */
static BOOL daArrow_Lighteff_Delete(void* i_this) {
    return static_cast<daArrow_Lighteff_c*>(i_this)->_delete();
}

bool daArrow_Lighteff_c::_draw() {
    if(field_0x2E9 == 0) {
        return true;
    }

    J3DModelData* modelData = field_0x298->getModelData();
    if(mDoGph_gInf_c::isMonotone()) {
        dComIfGd_setListP1();
    }
    else {
        dComIfGd_setListMaskOff();
    }

    mBtk.entry(modelData, mBtk.getFrame());
    mBrk.entry(modelData, mBrk.getFrame());
    mDoExt_modelUpdateDL(field_0x298);
    mBrk.remove(modelData);
    mBtk.remove(modelData);
    
    dComIfGd_setList();

    return true;
}

/* 00000C10-00000D20       .text daArrow_Lighteff_Draw__FPv */
static BOOL daArrow_Lighteff_Draw(void* i_this) {
    return static_cast<daArrow_Lighteff_c*>(i_this)->_draw();
}

/* 00000D20-00000D44       .text daArrow_Lighteff_Execute__FPv */
static BOOL daArrow_Lighteff_Execute(void* i_this) {
    return static_cast<daArrow_Lighteff_c*>(i_this)->_execute();
}

void daArrow_Lighteff_c::brk_play() {
    mBtk.play();

    int cam = dComIfGp_getPlayerCameraID(0);
    if(!dComIfGp_checkCameraAttentionStatus(cam, 0x20)) {
        if(field_0x2E0 < mBrk.getEndFrame()) {
            field_0x2E0 += 1.0f;
            if(field_0x2E0 > mBrk.getEndFrame()) {
                field_0x2E0 = mBrk.getEndFrame();
            }
        }
    }
    else {
        if(field_0x2E0 > 5.0f) {
            field_0x2E0 -= 1.0f;
            if(field_0x2E0 < 5.0f) {
                field_0x2E0 = 5.0f;
            }
        }
        else {
            if(field_0x2E0 < 5.0f) {
                field_0x2E0 += 1.0f;
                if(field_0x2E0 > 5.0f) {
                    field_0x2E0 = 5.0f;
                }
            }
        }
    }

    mBrk.setFrame(field_0x2E0);
}

/* 00000D44-000011A4       .text _execute__18daArrow_Lighteff_cFv */
bool daArrow_Lighteff_c::_execute() {
    field_0x2F0 = field_0x2EC;

    brk_play();

    daPy_py_c* link = daPy_getPlayerActorClass();
    daArrow_c* arrow = static_cast<daArrow_c*>(fopAcM_SearchByID(parentActorID));
    if(arrow) {
        field_0x2EC = fopAcM_GetParam(arrow);
        if(arrow->field_0x6e4 == 1) {
            fopAcM_delete(this);
        }
        else {
            if(field_0x2EC != 0) {
                if(field_0x2EC == 1) {
                    if(field_0x2F0 != 1) {
                        if(!arrow->isSetByZelda()) {
                            link->onUseArrowEffect();
                        }

                        field_0x2EA = 1;
                        field_0x2A8.z = 1.0f;
                    }
                    else {
                        field_0x2A8.z += 1.0;
                        if(field_0x2A8.z >= 20.0f) {
                            field_0x2A8.z = 20.0f;
                        }

                        field_0x2A8.x -= 0.025;
                        if(field_0x2A8.x <= 0.5f) {
                            field_0x2A8.x = 0.5f;
                        }

                        field_0x2A8.y = field_0x2A8.x;
                    }
                }
                else if(field_0x2EC == 3) {
                    fopAcM_delete(this);
                }
                else {
                    field_0x2E9 = 0;
                    delete_particle();
                    field_0x2E4++;
                    if(0x3C <= field_0x2E4) {
                        fopAcM_delete(this);
                    }
                }
            }
        }

        current.pos = arrow->current.pos;
        current.angle = arrow->field_0x6e6;
        setTopPos();
        setPointLight();
    }
    else {
        fopAcM_delete(this);
    }

    int cam = dComIfGp_getPlayerCameraID(0);
    if(field_0x2E8 == 1) {
        fopAcM_seStartCurrent(this, JA_SE_OBJ_FIRE_ARROW_AMB, 0);
        if(!dComIfGp_checkCameraAttentionStatus(cam, 0x20)) {
            dComIfGp_particle_setSimple(dPa_name::ID_COMMON_4004, &field_0x29C);
        }
    }
    else if(field_0x2E8 == 2) {
        fopAcM_seStartCurrent(this, JA_SE_OBJ_ICE_ARROW_AMB, 0);
        if(dComIfGp_checkCameraAttentionStatus(cam, 0x20)) {
            if(field_0x2F4.getEmitter()) {
                field_0x2F4.getEmitter()->setGlobalAlpha(0x64);
            }
            if(field_0x308.getEmitter()) {
                field_0x308.getEmitter()->setGlobalAlpha(0x64);
            }
        }
        else {
            if(field_0x2F4.getEmitter()) {
                field_0x2F4.getEmitter()->setGlobalAlpha(0xFF);
            }
            if(field_0x308.getEmitter()) {
                field_0x308.getEmitter()->setGlobalAlpha(0xFF);
            }
        }
    }
    else {
        fopAcM_seStartCurrent(this, JA_SE_OBJ_LIGHT_ARROW_AMB, 0);
    }

    set_mtx();

    return true;
}

/* 000011A4-000011AC       .text daArrow_Lighteff_IsDelete__FPv */
static BOOL daArrow_Lighteff_IsDelete(void*) {
    return true;
}

static actor_method_class daArrow_LighteffMethodTable = {
    (process_method_func)daArrow_Lighteff_Create,
    (process_method_func)daArrow_Lighteff_Delete,
    (process_method_func)daArrow_Lighteff_Execute,
    (process_method_func)daArrow_Lighteff_IsDelete,
    (process_method_func)daArrow_Lighteff_Draw,
};

actor_process_profile_definition g_profile_ARROW_LIGHTEFF = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0009,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_ARROW_LIGHTEFF,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daArrow_Lighteff_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x01C1,
    /* Actor SubMtd */ &daArrow_LighteffMethodTable,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
