//
// Generated by dtk
// Translation Unit: d_a_warpls.cpp
//

#include "d/actor/d_a_warpls.h"
#include "d/d_procname.h"

/* 00000078-000000E0       .text _delete__10daWarpls_cFv */
BOOL daWarpls_c::_delete() {
    /* Nonmatching */
}

/* 000000E0-00000100       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00000100-000003D8       .text CreateHeap__10daWarpls_cFv */
void daWarpls_c::CreateHeap() {
    /* Nonmatching */
}

/* 00000420-00000764       .text CreateInit__10daWarpls_cFv */
void daWarpls_c::CreateInit() {
    /* Nonmatching */
}

/* 00000764-0000082C       .text _create__10daWarpls_cFv */
s32 daWarpls_c::_create() {
    /* Nonmatching */
}

/* 0000082C-0000089C       .text set_mtx__10daWarpls_cFv */
void daWarpls_c::set_mtx() {
    /* Nonmatching */
}

/* 0000089C-00000984       .text _execute__10daWarpls_cFv */
BOOL daWarpls_c::_execute() {
    /* Nonmatching */
}

/* 00000984-00000AC4       .text checkOrder__10daWarpls_cFv */
void daWarpls_c::checkOrder() {
    /* Nonmatching */
}

/* 00000AC4-00000BFC       .text eventOrder__10daWarpls_cFv */
void daWarpls_c::eventOrder() {
    /* Nonmatching */
}

/* 00000BFC-00000C7C       .text setStatus__10daWarpls_cFv */
void daWarpls_c::setStatus() {
    /* Nonmatching */
}

/* 00000C7C-00000DC4       .text demo__10daWarpls_cFv */
void daWarpls_c::demo() {
    /* Nonmatching */
}

/* 00000DC4-00000EE8       .text check_warp_link__10daWarpls_cFv */
void daWarpls_c::check_warp_link() {
    /* Nonmatching */
}

/* 00000EE8-00000FF4       .text check_warp_distance__10daWarpls_cFv */
void daWarpls_c::check_warp_distance() {
    /* Nonmatching */
}

/* 00000FF4-000010C8       .text warp_eff_start__10daWarpls_cFv */
void daWarpls_c::warp_eff_start() {
    /* Nonmatching */
}

/* 000010C8-000010E8       .text daWarpls_Create__FPv */
static s32 daWarpls_Create(void*) {
    /* Nonmatching */
}

/* 000010E8-0000110C       .text daWarpls_Delete__FPv */
static BOOL daWarpls_Delete(void*) {
    /* Nonmatching */
}

/* 0000110C-000011D0       .text daWarpls_Draw__FPv */
static BOOL daWarpls_Draw(void*) {
    /* Nonmatching */
}

/* 000011D0-000011F4       .text daWarpls_Execute__FPv */
static BOOL daWarpls_Execute(void*) {
    /* Nonmatching */
}

/* 000011F4-000011FC       .text daWarpls_IsDelete__FPv */
static BOOL daWarpls_IsDelete(void*) {
    /* Nonmatching */
}


static actor_method_class daWarplsMethodTable = {
    (process_method_func)daWarpls_Create,
    (process_method_func)daWarpls_Delete,
    (process_method_func)daWarpls_Execute,
    (process_method_func)daWarpls_IsDelete,
    (process_method_func)daWarpls_Draw,
};

actor_process_profile_definition g_profile_WARPLIGHT = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_WARPLIGHT,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daWarpls_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x01A4,
    /* Actor SubMtd */ &daWarplsMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
