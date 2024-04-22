//
// Generated by dtk
// Translation Unit: d_a_bmd.cpp
//

#include "d/actor/d_a_bmd.h"
#include "d/d_procname.h"

/* 000000EC-00000134       .text __ct__11daBmd_HIO_cFv */
daBmd_HIO_c::daBmd_HIO_c() {
    /* Nonmatching */
}

/* 00000134-00000240       .text core_nodeCallBack__FP7J3DNodei */
static BOOL core_nodeCallBack(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000240-000002CC       .text mk_draw__FP9bmd_class */
void mk_draw(bmd_class*) {
    /* Nonmatching */
}

/* 000002CC-000005C8       .text daBmd_Draw__FP9bmd_class */
static BOOL daBmd_Draw(bmd_class*) {
    /* Nonmatching */
}

/* 00000604-00000734       .text anm_init__FP9bmd_classifUcfi */
void anm_init(bmd_class*, int, float, unsigned char, float, int) {
    /* Nonmatching */
}

/* 00000734-000010A4       .text damage__FP9bmd_class */
void damage(bmd_class*) {
    /* Nonmatching */
}

/* 000010A4-00001530       .text eat__FP9bmd_class */
void eat(bmd_class*) {
    /* Nonmatching */
}

/* 00001530-00001684       .text move1__FP9bmd_class */
void move1(bmd_class*) {
    /* Nonmatching */
}

/* 00001684-00001B48       .text start__FP9bmd_class */
void start(bmd_class*) {
    /* Nonmatching */
}

/* 00001B48-00001EFC       .text end__FP9bmd_class */
void end(bmd_class*) {
    /* Nonmatching */
}

/* 00001EFC-00002190       .text core_damage_check__FP9bmd_class */
void core_damage_check(bmd_class*) {
    /* Nonmatching */
}

/* 000021CC-00002EDC       .text core_move__FP9bmd_class */
void core_move(bmd_class*) {
    /* Nonmatching */
}

/* 00002EDC-00002F40       .text mk_voice_set__FP9bmd_classUl */
void mk_voice_set(bmd_class*, unsigned long) {
    /* Nonmatching */
}

/* 00002F40-0000330C       .text mk_move__FP9bmd_class */
void mk_move(bmd_class*) {
    /* Nonmatching */
}

/* 0000330C-0000339C       .text damage_check__FP9bmd_class */
void damage_check(bmd_class*) {
    /* Nonmatching */
}

/* 0000339C-00003910       .text wait__FP9bmd_class */
void wait(bmd_class*) {
    /* Nonmatching */
}

/* 00003910-000039A4       .text attack_1__FP9bmd_class */
void attack_1(bmd_class*) {
    /* Nonmatching */
}

/* 000039A4-00003A78       .text attack_2__FP9bmd_class */
void attack_2(bmd_class*) {
    /* Nonmatching */
}

/* 00003A78-00003BDC       .text move__FP9bmd_class */
void move(bmd_class*) {
    /* Nonmatching */
}

/* 00003BDC-00003D48       .text eff_cont__FP9bmd_class */
void eff_cont(bmd_class*) {
    /* Nonmatching */
}

/* 00003D48-00003E38       .text ride_call_back__FP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void ride_call_back(dBgW*, fopAc_ac_c*, fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00003E38-000054D4       .text demo_camera__FP9bmd_class */
void demo_camera(bmd_class*) {
    /* Nonmatching */
}

/* 000054D4-000055EC       .text bmd_kankyo__FP9bmd_class */
void bmd_kankyo(bmd_class*) {
    /* Nonmatching */
}

/* 000055EC-00005BF4       .text daBmd_Execute__FP9bmd_class */
static BOOL daBmd_Execute(bmd_class*) {
    /* Nonmatching */
}

/* 00005BF4-00005BFC       .text daBmd_IsDelete__FP9bmd_class */
static BOOL daBmd_IsDelete(bmd_class*) {
    /* Nonmatching */
}

/* 00005BFC-00005CF4       .text daBmd_Delete__FP9bmd_class */
static BOOL daBmd_Delete(bmd_class*) {
    /* Nonmatching */
}

/* 00005CF4-000064C0       .text useHeapInit__FP9bmd_class */
void useHeapInit(bmd_class*) {
    /* Nonmatching */
}

/* 00006508-00006528       .text solidHeapCB__FP10fopAc_ac_c */
static BOOL solidHeapCB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00006528-00006908       .text daBmd_Create__FP10fopAc_ac_c */
static s32 daBmd_Create(fopAc_ac_c*) {
    /* Nonmatching */
}


static actor_method_class l_daBmd_Method = {
    (process_method_func)daBmd_Create,
    (process_method_func)daBmd_Delete,
    (process_method_func)daBmd_Execute,
    (process_method_func)daBmd_IsDelete,
    (process_method_func)daBmd_Draw,
};

actor_process_profile_definition g_profile_BMD = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BMD,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(bmd_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x00DF,
    /* Actor SubMtd */ &l_daBmd_Method,
    /* Status       */ fopAcStts_SHOWMAP_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e | fopAcStts_BOSS_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
