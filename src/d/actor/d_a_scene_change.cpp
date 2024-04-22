//
// Generated by dtk
// Translation Unit: d_a_scene_change.cpp
//

#include "d/actor/d_a_scene_change.h"
#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_hostIO.h"
#include "d/d_procname.h"

static daSceneChgHIO_c l_HIO;

/* 000000EC-00000118       .text __ct__15daSceneChgHIO_cFv */
daSceneChgHIO_c::daSceneChgHIO_c() {
    m0004 = 0xFF;
    m0005 = 0;
    m0008 = 100.0f;
}

/* 00000118-000001A8       .text daSceneChgCreate__FPv */
static s32 daSceneChgCreate(void* i_this) {
    d_a_scene_change_c* scnChg = static_cast<d_a_scene_change_c*>(i_this);
    
    fopAcM_SetupActor(scnChg, d_a_scene_change_c);
    
    mDoMtx_stack_c::transS(scnChg->current.pos);
    mDoMtx_stack_c::ZXYrotM(scnChg->shape_angle);
    
    cMtx_copy(mDoMtx_stack_c::get(), scnChg->mTransformMtx);
    return cPhs_COMPLEATE_e;
}

/* 000001A8-000001B0       .text daSceneChgDelete__FPv */
static BOOL daSceneChgDelete(void* i_this) {
    return TRUE;
}

/* 000001B0-000001B8       .text daSceneChgExecute__FPv */
static BOOL daSceneChgExecute(void* i_this) {
    return TRUE;
}

/* 000001B8-000001C0       .text daSceneChgDraw__FPv */
static BOOL daSceneChgDraw(void* i_this) {
    return TRUE;
}

/* 000001C0-000001C8       .text daSceneChgIsDelete__FPv */
static BOOL daSceneChgIsDelete(void* i_this) {
    return TRUE;
}

static actor_method_class daSceneChgMethodTable = {
    (process_method_func)daSceneChgCreate,
    (process_method_func)daSceneChgDelete,
    (process_method_func)daSceneChgExecute,
    (process_method_func)daSceneChgIsDelete,
    (process_method_func)daSceneChgDraw,
};

actor_process_profile_definition g_profile_SCENECHG = {
    fpcLy_CURRENT_e,
    3,
    fpcLy_CURRENT_e,
    PROC_SCENECHG,
    &g_fpcLf_Method.base,
    sizeof(d_a_scene_change_c),
    0,
    0,
    &g_fopAc_Method.base,
    0x01A1,
    &daSceneChgMethodTable,
    fopAcStts_UNK40000_e,
    fopAc_ACTOR_e,
    fopAc_CULLBOX_4_e,
};
