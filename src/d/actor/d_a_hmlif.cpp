//
// Generated by dtk
// Translation Unit: d_a_hmlif.cpp
//

#include "d/actor/d_a_hmlif.h"
#include "d/d_procname.h"

/* 00000078-00000080       .text Delete__9daHmlif_cFv */
BOOL daHmlif_c::Delete() {
    /* Nonmatching */
}

/* 00000080-000000D8       .text daHmlifDelete__9daHmlif_cFv */
void daHmlif_c::daHmlifDelete() {
    /* Nonmatching */
}

/* 000000D8-0000042C       .text CreateHeap__9daHmlif_cFv */
void daHmlif_c::CreateHeap() {
    /* Nonmatching */
}

/* 00000474-000007C8       .text Create__9daHmlif_cFv */
s32 daHmlif_c::Create() {
    /* Nonmatching */
}

/* 000007C8-00000930       .text daHmlifCreate__9daHmlif_cFv */
cPhs_State daHmlif_c::daHmlifCreate() {
    /* Nonmatching */
}

/* 00000AE8-00000B80       .text set_mtx__9daHmlif_cFv */
void daHmlif_c::set_mtx() {
    /* Nonmatching */
}

/* 00000B80-00000BE4       .text Execute__9daHmlif_cFPPA3_A4_f */
void daHmlif_c::Execute(float(**)[3][4]) {
    /* Nonmatching */
}

/* 00000BE4-00000C24       .text move__9daHmlif_cFv */
void daHmlif_c::move() {
    /* Nonmatching */
}

/* 00000C24-00000CA8       .text set_se__9daHmlif_cFv */
void daHmlif_c::set_se() {
    /* Nonmatching */
}

/* 00000CA8-00000D94       .text anim_play__9daHmlif_cFv */
void daHmlif_c::anim_play() {
    /* Nonmatching */
}

/* 00000D94-00000F10       .text check_col__9daHmlif_cFv */
void daHmlif_c::check_col() {
    /* Nonmatching */
}

/* 00000F10-000010C4       .text lift_smooth_move__9daHmlif_cFv */
void daHmlif_c::lift_smooth_move() {
    /* Nonmatching */
}

/* 000010C4-00001270       .text lift_normal_move__9daHmlif_cFv */
void daHmlif_c::lift_normal_move() {
    /* Nonmatching */
}

/* 00001270-00001410       .text set_next_pnt__9daHmlif_cFv */
void daHmlif_c::set_next_pnt() {
    /* Nonmatching */
}

/* 00001410-00001520       .text setNextPath__9daHmlif_cFv */
void daHmlif_c::setNextPath() {
    /* Nonmatching */
}

/* 00001520-00001534       .text chkSwitchPathType__9daHmlif_cFv */
void daHmlif_c::chkSwitchPathType() {
    /* Nonmatching */
}

/* 00001534-00001610       .text Draw__9daHmlif_cFv */
BOOL daHmlif_c::Draw() {
    /* Nonmatching */
}

/* 00001610-00001630       .text daHmlif_Create__FPv */
static cPhs_State daHmlif_Create(void*) {
    /* Nonmatching */
}

/* 00001630-00001650       .text daHmlif_Delete__FPv */
static BOOL daHmlif_Delete(void*) {
    /* Nonmatching */
}

/* 00001650-0000167C       .text daHmlif_Draw__FPv */
static BOOL daHmlif_Draw(void*) {
    /* Nonmatching */
}

/* 0000167C-0000169C       .text daHmlif_Execute__FPv */
static BOOL daHmlif_Execute(void*) {
    /* Nonmatching */
}

/* 0000169C-000016A4       .text daHmlif_IsDelete__FPv */
static BOOL daHmlif_IsDelete(void*) {
    /* Nonmatching */
}

static actor_method_class daHmlifMethodTable = {
    (process_method_func)daHmlif_Create,
    (process_method_func)daHmlif_Delete,
    (process_method_func)daHmlif_Execute,
    (process_method_func)daHmlif_IsDelete,
    (process_method_func)daHmlif_Draw,
};

actor_process_profile_definition g_profile_Hmlif = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0002,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Hmlif,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daHmlif_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x008D,
    /* Actor SubMtd */ &daHmlifMethodTable,
    /* Status       */ 0x04 | fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
