//
// Generated by dtk
// Translation Unit: d_a_tori_flag.cpp
//

#include "d/actor/d_a_tori_flag.h"
#include "d/d_procname.h"

/* 000000EC-00000118       .text __ct__17daTori_Flag_HIO_cFv */
daTori_Flag_HIO_c::daTori_Flag_HIO_c() {
    /* Nonmatching */
}

/* 00000118-000001C4       .text set_mtx__13daTori_Flag_cFv */
void daTori_Flag_c::set_mtx() {
    /* Nonmatching */
}

/* 000001C4-000001E4       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000001E4-0000030C       .text CreateHeap__13daTori_Flag_cFv */
void daTori_Flag_c::CreateHeap() {
    /* Nonmatching */
}

/* 0000030C-000003A4       .text CreateInit__13daTori_Flag_cFv */
void daTori_Flag_c::CreateInit() {
    /* Nonmatching */
}

/* 000003A4-000003C4       .text daTori_FlagCreate__FPv */
static s32 daTori_FlagCreate(void*) {
    /* Nonmatching */
}

/* 000003C4-00000478       .text _create__13daTori_Flag_cFv */
s32 daTori_Flag_c::_create() {
    /* Nonmatching */
}

/* 00000804-00000854       .text daTori_FlagDelete__FPv */
static BOOL daTori_FlagDelete(void*) {
    /* Nonmatching */
}

/* 00000854-00000878       .text daTori_FlagExecute__FPv */
static BOOL daTori_FlagExecute(void*) {
    /* Nonmatching */
}

/* 00000878-00000B1C       .text _execute__13daTori_Flag_cFv */
BOOL daTori_Flag_c::_execute() {
    /* Nonmatching */
}

/* 00000B1C-00000BB8       .text daTori_FlagDraw__FPv */
static BOOL daTori_FlagDraw(void*) {
    /* Nonmatching */
}

/* 00000BB8-00000BC0       .text daTori_FlagIsDelete__FPv */
static BOOL daTori_FlagIsDelete(void*) {
    /* Nonmatching */
}


static actor_method_class daTori_FlagMethodTable = {
    (process_method_func)daTori_FlagCreate,
    (process_method_func)daTori_FlagDelete,
    (process_method_func)daTori_FlagExecute,
    (process_method_func)daTori_FlagIsDelete,
    (process_method_func)daTori_FlagDraw,
};

actor_process_profile_definition g_profile_Tori_Flag = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Tori_Flag,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daTori_Flag_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x006C,
    /* Actor SubMtd */ &daTori_FlagMethodTable,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_4_e,
};
