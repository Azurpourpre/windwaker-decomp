//
// Generated by dtk
// Translation Unit: d_a_shutter2.cpp
//

#include "d/actor/d_a_shutter2.h"
#include "d/d_procname.h"

/* 00000078-000000B8       .text Delete__12daShutter2_cFv */
BOOL daShutter2_c::Delete() {
    /* Nonmatching */
}

/* 000000B8-00000194       .text CreateHeap__12daShutter2_cFv */
void daShutter2_c::CreateHeap() {
    /* Nonmatching */
}

/* 00000194-00000350       .text Create__12daShutter2_cFv */
s32 daShutter2_c::Create() {
    /* Nonmatching */
}

/* 00000350-0000041C       .text _create__12daShutter2_cFv */
s32 daShutter2_c::_create() {
    /* Nonmatching */
}

/* 0000041C-000004AC       .text set_mtx__12daShutter2_cFv */
void daShutter2_c::set_mtx() {
    /* Nonmatching */
}

/* 000004AC-00000528       .text Execute__12daShutter2_cFPPA3_A4_f */
void daShutter2_c::Execute(float(**)[3][4]) {
    /* Nonmatching */
}

/* 00000528-00000698       .text shutter_move__12daShutter2_cFv */
void daShutter2_c::shutter_move() {
    /* Nonmatching */
}

/* 00000698-000008B0       .text demo__12daShutter2_cFv */
void daShutter2_c::demo() {
    /* Nonmatching */
}

/* 000008B0-00000950       .text Draw__12daShutter2_cFv */
BOOL daShutter2_c::Draw() {
    /* Nonmatching */
}

/* 00000950-00000970       .text daShutter2_Create__FPv */
static s32 daShutter2_Create(void*) {
    /* Nonmatching */
}

/* 00000970-00000990       .text daShutter2_Delete__FPv */
static BOOL daShutter2_Delete(void*) {
    /* Nonmatching */
}

/* 00000990-000009BC       .text daShutter2_Draw__FPv */
static BOOL daShutter2_Draw(void*) {
    /* Nonmatching */
}

/* 000009BC-000009DC       .text daShutter2_Execute__FPv */
static BOOL daShutter2_Execute(void*) {
    /* Nonmatching */
}

/* 000009DC-000009E4       .text daShutter2_IsDelete__FPv */
static BOOL daShutter2_IsDelete(void*) {
    /* Nonmatching */
}


static actor_method_class daShutter2MethodTable = {
    (process_method_func)daShutter2_Create,
    (process_method_func)daShutter2_Delete,
    (process_method_func)daShutter2_Execute,
    (process_method_func)daShutter2_IsDelete,
    (process_method_func)daShutter2_Draw,
};

actor_process_profile_definition g_profile_SHUTTER2 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_SHUTTER2,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daShutter2_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x01BB,
    /* Actor SubMtd */ &daShutter2MethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
