//
// Generated by dtk
// Translation Unit: d_a_kui.cpp
//

#include "d/actor/d_a_kui.h"
#include "d/d_procname.h"

class J3DModelData;

/* 00000078-000000C4       .text s_a_i_sub__FPvPv */
void s_a_i_sub(void*, void*) {
    /* Nonmatching */
}

/* 000000C4-000000F0       .text search_dragontail__FP9kui_class */
void search_dragontail(kui_class*) {
    /* Nonmatching */
}

/* 000000F0-0000013C       .text b_a_i_sub__FPvPv */
void b_a_i_sub(void*, void*) {
    /* Nonmatching */
}

/* 0000013C-00000168       .text search_btd__FP9kui_class */
void search_btd(kui_class*) {
    /* Nonmatching */
}

/* 00000168-0000037C       .text setEffectMtx__FP10fopAc_ac_cP12J3DModelDataf */
void setEffectMtx(fopAc_ac_c*, J3DModelData*, float) {
    /* Nonmatching */
}

/* 0000037C-00000540       .text daKui_Draw__FP9kui_class */
static BOOL daKui_Draw(kui_class*) {
    /* Nonmatching */
}

/* 00000540-00000920       .text demo_camera__FP9kui_class */
void demo_camera(kui_class*) {
    /* Nonmatching */
}

/* 00000920-000012E4       .text daKui_Execute__FP9kui_class */
static BOOL daKui_Execute(kui_class*) {
    /* Nonmatching */
}

/* 000012E4-000012EC       .text daKui_IsDelete__FP9kui_class */
static BOOL daKui_IsDelete(kui_class*) {
    /* Nonmatching */
}

/* 000012EC-00001340       .text daKui_Delete__FP9kui_class */
static BOOL daKui_Delete(kui_class*) {
    /* Nonmatching */
}

/* 00001340-00001664       .text daKui_CreateHeap__FP10fopAc_ac_c */
static BOOL daKui_CreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00001664-000018C8       .text daKui_Create__FP10fopAc_ac_c */
static s32 daKui_Create(fopAc_ac_c*) {
    /* Nonmatching */
}


static actor_method_class l_daKui_Method = {
    (process_method_func)daKui_Create,
    (process_method_func)daKui_Delete,
    (process_method_func)daKui_Execute,
    (process_method_func)daKui_IsDelete,
    (process_method_func)daKui_Draw,
};

actor_process_profile_definition g_profile_KUI = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_KUI,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(kui_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x00F0,
    /* Actor SubMtd */ &l_daKui_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
