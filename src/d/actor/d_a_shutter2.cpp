//
// Generated by dtk
// Translation Unit: d_a_shutter2.cpp
//

#include "d/actor/d_a_shutter2.h"
#include "d/d_procname.h"
#include "d/d_com_inf_game.h"
#include "d/res/res_htobi3.h"

const float daShutter2_c::m_max_speed[1] = {3.0f};
const float daShutter2_c::m_min_speed[1] = {1.0f};
const float daShutter2_c::m_move_len[1] = {350.0f};
const float daShutter2_c::m_width[1] = {500.0f};
const float daShutter2_c::m_height[1] = {400.0f};
const s16 daShutter2_c::m_bdlidx[1] = {HTOBI3_BDL_HTOBI3};
const s16 daShutter2_c::m_dzbidx[1] = {HTOBI3_DZB_HTOBI3};
const s32 daShutter2_c::m_heapsize[1] = {0x0C00};
const Vec daShutter2_c::m_cull_min[1] = {{-300.0f, -10.0f, -40.0f}};
const Vec daShutter2_c::m_cull_max[1] = {{300.0f, 400.0f, 40.0f}};

char* daShutter2_c::m_arcname[1] = {"Htobi3"};
char* daShutter2_c::m_open_ev_name[1] = {"R04DOOROPEN"};
char* daShutter2_c::m_close_ev_name[1] = {"R04DOORCLOSE"};
char* daShutter2_c::m_staff_name[1] = {"Htobi3"};

/* 00000078-000000B8       .text Delete__12daShutter2_cFv */
BOOL daShutter2_c::Delete() {
    dComIfG_resDelete(&mPhs, m_arcname[mType]);
    return TRUE;
}

/* 000000B8-00000194       .text CreateHeap__12daShutter2_cFv */
int daShutter2_c::CreateHeap() {
    J3DModelData* modelData = (J3DModelData *)dComIfG_getObjectRes(m_arcname[mType], m_bdlidx[mType]);
    JUT_ASSERT(0xe0, modelData != 0);
    mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
    if (!mpModel) {
        return FALSE;
    }
    return TRUE;
}

/* 00000194-00000350       .text Create__12daShutter2_cFv */
int daShutter2_c::Create() {
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    Vec cullMin = m_cull_min[mType];
    Vec cullMax = m_cull_max[mType];
    fopAcM_setCullSizeBox(this, cullMin.x, cullMin.y, cullMin.z, cullMax.x, cullMax.y, cullMax.z);
    mSwitchNo = daShutter2_prm::getSwitchNo(this);
    mbIsNearEnemy = fopAcM_myRoomSearchEnemy(fopAcM_GetRoomNo(this)) == NULL;
    if (((mSwitchNo != 0xff) && (fopAcM_isSwitch(this, mSwitchNo))) ||
        ((mSwitchNo == 0xff) && (mbIsNearEnemy))) {
        m30C = 1;
        current.pos.y = home.pos.y + 350.0f;
    }
    else {
        m30C = 2;
    }
    mbIsSwitch = fopAcM_isSwitch(this, mSwitchNo);
    set_mtx();
    if (m_open_ev_name[mType] != NULL) {
        mOpenEventIdx = dComIfGp_evmng_getEventIdx(m_open_ev_name[mType], 0xff);
    }
    if (m_close_ev_name[mType] != NULL) {
        mCloseEventIdx = dComIfGp_evmng_getEventIdx(m_close_ev_name[mType], 0xff);
    }
    return TRUE;
}

/* 00000350-0000041C       .text _create__12daShutter2_cFv */
s32 daShutter2_c::_create() {
    fopAcM_SetupActor(this, daShutter2_c);
    mType = 0;
    int phase_state = dComIfG_resLoad(&mPhs, m_arcname[mType]);
    if (phase_state == cPhs_COMPLEATE_e) {
        phase_state = MoveBGCreate(m_arcname[mType], m_dzbidx[mType], NULL, m_heapsize[mType]);
        if (phase_state == cPhs_ERROR_e) {
            phase_state = cPhs_ERROR_e;
        }
    }
    return phase_state;
}

/* 0000041C-000004AC       .text set_mtx__12daShutter2_cFv */
void daShutter2_c::set_mtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    MTXCopy(mDoMtx_stack_c::get(), mMtx);
    return;
}

/* 000004AC-00000528       .text Execute__12daShutter2_cFPPA3_A4_f */
BOOL daShutter2_c::Execute(Mtx** pMtx) {
    demo();
    set_mtx();
    mbIsSwitch = fopAcM_isSwitch(this, mSwitchNo);
    mbIsNearEnemy = fopAcM_myRoomSearchEnemy(fopAcM_GetRoomNo(this)) == NULL;
    *pMtx = &mMtx;
    return TRUE;
}

/* 00000528-00000698       .text shutter_move__12daShutter2_cFv */
void daShutter2_c::shutter_move() {
    float fVar3;

    static char* action_table[4] = {
        "WAIT",
        "OPEN",
        "CLOSE",
        "OPEN_INIT",
    };
    enum {
        ACT_WAIT,
        ACT_OPEN,
        ACT_CLOSE,
        ACT_OPEN_INIT,
    };
    int actionIndex = dComIfGp_evmng_getMyActIdx(mStaffId, action_table, ARRAY_SIZE(action_table), FALSE, 0);

    float maxVel = m_max_speed[mType];
    float minVel = m_min_speed[mType];
    
    switch (actionIndex) {
        case ACT_WAIT:
        {
            dComIfGp_evmng_cutEnd(mStaffId);
            break;   
        }
        case ACT_OPEN_INIT:
        {
            fopAcM_seStart(this, JA_SE_OBJ_WDUN_R04_STR_OP, 0);
            dComIfGp_evmng_cutEnd(mStaffId);
            break;
        }
        case ACT_OPEN:
        {
            fVar3 = cLib_addCalc(&current.pos.y, home.pos.y + 350.0f, 0.1f, maxVel, minVel);
            if (fVar3 == 0.0f){
                dComIfGp_evmng_cutEnd(mStaffId);
            }
            break;

        }
        case ACT_CLOSE:
        {
            fVar3 = cLib_addCalc(&current.pos.y, home.pos.y, 0.1f, maxVel, minVel);
            if (fVar3 == 0.0f){
                dComIfGp_evmng_cutEnd(mStaffId);
            }
            break;
        }
        default:
            dComIfGp_evmng_cutEnd(mStaffId);
            break;
    }
    return;
}

/* 00000698-000008B0       .text demo__12daShutter2_cFv */
void daShutter2_c::demo() {
    u8 isSwitch = fopAcM_isSwitch(this, mSwitchNo);
    u8 isNearEnemy = fopAcM_myRoomSearchEnemy(fopAcM_GetRoomNo(this)) == NULL;
    if (mDemoState == 0) {
        if (mSwitchNo != 0xFF) {
            if (isSwitch != mbIsSwitch) {
                if (!isSwitch) {
                    mDemoState = 2;
                }
                else {
                    mDemoState = 1;
                }
            }
        }
        else if (isNearEnemy != mbIsNearEnemy) {
            if (!isNearEnemy) {
                mDemoState = 2;
            }
            else {
                mDemoState = 1;
            }
        }
    }
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (dComIfGp_evmng_startCheck(mOpenEventIdx) && (mDemoState == 1)) {
            mDemoState = 0;
        }
        if (dComIfGp_evmng_startCheck(mCloseEventIdx) && (mDemoState == 2)) {
            mDemoState = 0;
        }
        if (dComIfGp_evmng_endCheck(mOpenEventIdx) || dComIfGp_evmng_endCheck(mCloseEventIdx)) {
            dComIfGp_event_reset();
        }
        mStaffId = dComIfGp_evmng_getMyStaffId(m_staff_name[mType], NULL, 0);
        shutter_move();
    }
    else if ((mDemoState == 1) && (mOpenEventIdx != 0)) {
        fopAcM_orderOtherEventId(this, mOpenEventIdx);
        eventInfo.onCondition(dEvtCnd_UNK2_e);
    }
    else if ((mDemoState == 2) && (mCloseEventIdx != 0)) {
        fopAcM_orderOtherEventId(this, mCloseEventIdx);
        eventInfo.onCondition(dEvtCnd_UNK2_e);
    }
    return;
}

/* 000008B0-00000950       .text Draw__12daShutter2_cFv */
BOOL daShutter2_c::Draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();
    return TRUE;
}

/* 00000950-00000970       .text daShutter2_Create__FPv */
static s32 daShutter2_Create(void* i_this) {
    return ((daShutter2_c*)i_this)->_create();
}

/* 00000970-00000990       .text daShutter2_Delete__FPv */
static BOOL daShutter2_Delete(void* i_this) {
    return ((daShutter2_c*)i_this)->MoveBGDelete();
}

/* 00000990-000009BC       .text daShutter2_Draw__FPv */
static BOOL daShutter2_Draw(void* i_this) {
    return ((daShutter2_c*)i_this)->MoveBGDraw();
}

/* 000009BC-000009DC       .text daShutter2_Execute__FPv */
static BOOL daShutter2_Execute(void* i_this) {
    return ((daShutter2_c*)i_this)->MoveBGExecute();
}

/* 000009DC-000009E4       .text daShutter2_IsDelete__FPv */
static BOOL daShutter2_IsDelete(void*) {
    return TRUE;
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
