//
// Generated by dtk
// Translation Unit: d_a_obj_ebomzo.cpp
//

#include "d/actor/d_a_obj_ebomzo.h"
#include "d/d_procname.h"

/* 00000078-0000012C       .text CreateHeap__Q211daObjEbomzo5Act_cFv */
void daObjEbomzo::Act_c::CreateHeap() {
    /* Nonmatching */
}

/* 0000012C-0000021C       .text Create__Q211daObjEbomzo5Act_cFv */
s32 daObjEbomzo::Act_c::Create() {
    /* Nonmatching */
}

/* 0000021C-000003A0       .text Mthd_Create__Q211daObjEbomzo5Act_cFv */
void daObjEbomzo::Act_c::Mthd_Create() {
    /* Nonmatching */
}

/* 00000558-00000560       .text Delete__Q211daObjEbomzo5Act_cFv */
BOOL daObjEbomzo::Act_c::Delete() {
    /* Nonmatching */
}

/* 00000560-000005AC       .text Mthd_Delete__Q211daObjEbomzo5Act_cFv */
void daObjEbomzo::Act_c::Mthd_Delete() {
    /* Nonmatching */
}

/* 000005AC-0000062C       .text set_mtx__Q211daObjEbomzo5Act_cFv */
void daObjEbomzo::Act_c::set_mtx() {
    /* Nonmatching */
}

/* 0000062C-00000668       .text init_mtx__Q211daObjEbomzo5Act_cFv */
void daObjEbomzo::Act_c::init_mtx() {
    /* Nonmatching */
}

/* 00000668-00000864       .text check__Q211daObjEbomzo5Act_cFv */
void daObjEbomzo::Act_c::check() {
    /* Nonmatching */
}

/* 00000864-000009BC       .text demo__Q211daObjEbomzo5Act_cFv */
void daObjEbomzo::Act_c::demo() {
    /* Nonmatching */
}

/* 000009BC-000009C0       .text fall__Q211daObjEbomzo5Act_cFv */
void daObjEbomzo::Act_c::fall() {
    /* Nonmatching */
}

/* 000009C0-00000AFC       .text Execute__Q211daObjEbomzo5Act_cFPPA3_A4_f */
void daObjEbomzo::Act_c::Execute(float(**)[3][4]) {
    /* Nonmatching */
}

/* 00000AFC-00000B9C       .text Draw__Q211daObjEbomzo5Act_cFv */
BOOL daObjEbomzo::Act_c::Draw() {
    /* Nonmatching */
}

namespace daObjEbomzo {
namespace {
static actor_method_class Mthd_Ebomzo = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjEbomzo

actor_process_profile_definition g_profile_Obj_Ebomzo = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Ebomzo,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjEbomzo::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x007C,
    /* Actor SubMtd */ &daObjEbomzo::Mthd_Ebomzo,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
