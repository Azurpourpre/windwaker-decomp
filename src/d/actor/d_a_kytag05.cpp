//
// Generated by dtk
// Translation Unit: d_a_kytag05.cpp
//
#include "JSystem/JKernel/JKRHeap.h"
#include "JAZelAudio/JAIZelBasic.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_player_link.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_camera_mng.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo_wether.h"
#include "d/actor/d_a_ykgr.h"
#include "m_Do/m_Do_audio.h"
#include "d/d_procname.h"


class kytag05_class : public fopAc_ac_c {
public:
    /* 0x290 */ u8 mIndex;
    /* 0x294 */ int mTimer;
    /* 0x298 */ int mUnknownParam;
}; /* size = 0x29C */

static BOOL daKytag05_Draw(kytag05_class*) {
    return TRUE;
}

/* 00000080-000003F4       .text daKytag05_Execute__FP13kytag05_class */
static BOOL daKytag05_Execute(kytag05_class* a_this) {
    static const s16 wind_table[] = {
        0x0000,
        0x8001,
        0xC000,
        0x4000,
    };
    static const s16 mufuu_timer[] = {
        10,
        10,
        0,
        90
    };
    static const s16 fuu_timer[] = {
        150,
        150,
        150,
        150,
    };
    
    camera_process_class *camera = dComIfGp_getCamera(0);
    fopAc_ac_c *player = dComIfGp_getPlayer(0);
    f32 windPow = dKyw_get_wind_pow();
    f32 i_blend = 1.0f;

    if (g_env_light.mWind.mEvtWindSet == 0xFF) {
        return TRUE;
    }
    
    if (dComIfGp_event_runCheck() && dComIfGp_evmng_startCheck("demo41") &&
        g_dComIfG_gameInfo.play.getDemo()) {
        u32 demoFrame = dComIfGp_demo_get()->getFrame();
        if(demoFrame >= 0x186) {
            f32 fVar7 = ((f32)demoFrame - 390.0f) / 100.0f;
            if(fVar7 > i_blend) {
                fVar7 = i_blend;
            }
            i_blend = 1.0f - fVar7;
            g_env_light.mSnowCount = (int)(200.0f * i_blend);
        } else if (demoFrame == 0x187) {
            daYkgr_c::stop();
        }
    }
    dKy_custom_colset(0, 7, i_blend);
    
    if((a_this->mIndex & 1) == 0) {
        if (a_this->mTimer >= fuu_timer[a_this->mIndex >> 1]) {
            a_this->mTimer = 0;
            a_this->mIndex += 1;
            g_env_light.mWind.mEvtWindSet = 2;
        } else {
            a_this->mTimer += 1;
        }
    } else {
        if (a_this->mTimer >= mufuu_timer[a_this->mIndex >> 1]) {
            a_this->mIndex += 1;
            if(a_this->mIndex >> 1 >= 4) {
                a_this->mIndex = 0;
            }
            dKyw_evt_wind_set(0, wind_table[a_this->mIndex >> 1]);
            a_this->mTimer = 0;
            g_env_light.mWind.mEvtWindSet = 1;
        } else {
            a_this->mTimer += 1;
        }
    }
    
    if((camera->mLookat.mEye.z > 1445.0f || player->current.pos.z > 1445.0f) &&
       (camera->mLookat.mEye.x > 520.0f || player->current.pos.x > 520.0f)){
        if(camera->mLookat.mEye.z > 2100.0f || player->current.pos.z > 2100.0f) {
            dKyw_evt_wind_set(0, 0x61A8);
        } else if(camera->mLookat.mEye.z > 1970.0f || player->current.pos.z > 1970.0f) {
            dKyw_evt_wind_set(0, 0x4E20);
        } else {
            dKyw_evt_wind_set(0, 0x4650);
        }
    } else if(camera->mLookat.mEye.z < -4085.0f || player->current.pos.z < -4085.0f) {
        dKyw_evt_wind_set(0, -0x3E80);
    } else if(camera->mLookat.mEye.z < -3108.0f || player->current.pos.z < -3108.0f) {
        dKyw_evt_wind_set(0, -0x4B00);
    } else if(camera->mLookat.mEye.z < -1412.0f || player->current.pos.z < -1412.0f) {
        dKyw_evt_wind_set(0, -0x32C8);
    }

    mDoAud_seStart(0x106A, 0, windPow * 100.0f, 0);
    
    return TRUE;
}

static BOOL daKytag05_IsDelete(kytag05_class*) {
    return TRUE;
}

static BOOL daKytag05_Delete(kytag05_class*) {
    return TRUE;
}

static int daKytag05_Create(fopAc_ac_c* i_this) {
    fopAcM_SetupActor(i_this, kytag05_class);
    kytag05_class *a_this = (kytag05_class*)i_this;
    if (dComIfGs_isSymbol(1) != 0) {
        return 3;
    }
    a_this->mIndex = 0;
    a_this->mTimer = 0;
    a_this->mUnknownParam = i_this->mBase.mParameters & 0xff;
    dKyw_evt_wind_set_go();
    dKyw_evt_wind_set(0, 0);
    g_env_light.mSnowCount = 200;
#if VERSION == VERSION_JPN
    g_env_light.mMoyaMode = 3;
#else
    g_env_light.mMoyaMode = 0;
#endif
    g_env_light.mMoyaCount = 100;

    return cPhs_COMPLEATE_e;
}

static actor_method_class l_daKytag05_Method = {
    (process_method_func)daKytag05_Create,
    (process_method_func)daKytag05_Delete,
    (process_method_func)daKytag05_Execute,
    (process_method_func)daKytag05_IsDelete,
    (process_method_func)daKytag05_Draw,
};

extern actor_process_profile_definition g_profile_KYTAG05 = {
    fpcLy_CURRENT_e,
    7,
    fpcLy_CURRENT_e,
    PROC_KYTAG05,
    &g_fpcLf_Method.mBase,
    sizeof(kytag05_class),
    0,
    0,
    &g_fopAc_Method.base,
    0xA5,
    &l_daKytag05_Method,
    fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    fopAc_ACTOR_e,
    fopAc_CULLBOX_0_e,
};