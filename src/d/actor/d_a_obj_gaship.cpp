//
// Generated by dtk
// Translation Unit: d_a_obj_gaship.cpp
//

#include "d/actor/d_a_obj_gaship.h"
#include "d/d_procname.h"

/* 000000EC-000002DC       .text birth_flag__Q211daObjGaship5Act_cFv */
void daObjGaship::Act_c::birth_flag() {
    /* Nonmatching */
}

/* 00000354-00000378       .text solidHeapCB__Q211daObjGaship5Act_cFP10fopAc_ac_c */
void daObjGaship::Act_c::solidHeapCB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00000378-00000448       .text create_heap__Q211daObjGaship5Act_cFv */
void daObjGaship::Act_c::create_heap() {
    /* Nonmatching */
}

/* 00000448-000004F8       .text _create__Q211daObjGaship5Act_cFv */
s32 daObjGaship::Act_c::_create() {
    /* Nonmatching */
}

/* 000004F8-00000528       .text _delete__Q211daObjGaship5Act_cFv */
BOOL daObjGaship::Act_c::_delete() {
    /* Nonmatching */
}

/* 00000528-000005D4       .text set_mtx__Q211daObjGaship5Act_cFv */
void daObjGaship::Act_c::set_mtx() {
    /* Nonmatching */
}

/* 000005D4-0000060C       .text _execute__Q211daObjGaship5Act_cFv */
BOOL daObjGaship::Act_c::_execute() {
    /* Nonmatching */
}

/* 0000060C-0000066C       .text _draw__Q211daObjGaship5Act_cFv */
BOOL daObjGaship::Act_c::_draw() {
    /* Nonmatching */
}

namespace daObjGaship {
namespace {
static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjGaship

actor_process_profile_definition g_profile_Obj_Gaship = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Gaship,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjGaship::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x003F,
    /* Actor SubMtd */ &daObjGaship::Mthd_Table,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
