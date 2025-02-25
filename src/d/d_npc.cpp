//
// Generated by dtk
// Translation Unit: d_npc.cpp
//

#include "d/d_npc.h"
#include "d/d_com_inf_game.h"
#include "d/actor/d_a_player.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_msg_mng.h"
#include "SSystem/SComponent/c_math.h"
#include "m_Do/m_Do_mtx.h"
#include "d/d_item_data.h"

#include "weak_data_1811.h" // IWYU pragma: keep

/* 8021A7B4-8021A858       .text angCalcS__14dNpc_JntCtrl_cFPssss */
bool dNpc_JntCtrl_c::angCalcS(s16* out, s16 targetY, s16 speed, s16 maxVel) {
    s16 diff = *out - targetY;
    int origDiff = diff;
    cLib_addCalcAngleS(&diff, 0, speed, maxVel, 0x60);
    if(abs(diff) > speed) {
        *out += diff - origDiff;
    }
    else {
        *out = targetY;
    }

    return (s16)targetY - *out == 0;
}

/* 8021A858-8021A884       .text limitter__14dNpc_JntCtrl_cFPsss */
void dNpc_JntCtrl_c::limitter(s16* targetDiff, s16 maxDiff, s16 minDiff) {
    if(*targetDiff > maxDiff) {
        *targetDiff = maxDiff;
    }
    if(*targetDiff < minDiff) {
        *targetDiff = minDiff;
    }
}

/* 8021A884-8021A97C       .text follow__14dNpc_JntCtrl_cFPsssi */
bool dNpc_JntCtrl_c::follow(s16* outY, s16 targetY, s16 maxVel, int param_4) {
    s16 origY = *outY;
    angCalcS(outY, targetY, 4, maxVel);
    s16 deltaY = *outY - origY;
    
    s16 sVar6 = 0;
    s16 sVar5 = 0;
    s16 sVar1 = targetY - *outY;
    for (int i = 1; i >= 0; i--) {
        sVar5 += mAngles[i][param_4];
        if ((deltaY > 0 && sVar5 > sVar1) || (deltaY < 0 && sVar5 < sVar1)) {
            mAngles[i][param_4] = sVar1 - sVar6;
            limitter(&mAngles[i][param_4], mMaxAngles[i][param_4], mMinAngles[i][param_4]);
        }
        sVar6 += mAngles[i][param_4];
    }
    
    return targetY != *outY;
}

/* 8021A97C-8021AABC       .text move__14dNpc_JntCtrl_cFsi */
bool dNpc_JntCtrl_c::move(s16 param_1, int param_2) {
    s16 angle;
    s32 angleL;
    s16 angles[2];
    int r25;
    int i;
    
    for (i = 0; i < 2; i++) {
        if ((i == 0 && mbHeadLock == true) || (i == 1 && mbBackBoneLock == true)) {
            angle = 0;
        } else {
            angle = param_1;
        }
        limitter(&angle, mMaxAngles[i][param_2], mMinAngles[i][param_2]);
        param_1 -= (int)angle;
        angles[i] = angle;
        angleL = mAngles[i][param_2];
        cLib_addCalcAngleL(&angleL, angle, 4, mMaxTurnStep[i][param_2], 1);
        mAngles[i][param_2] = angleL;
    }
    
    for (i = 0, r25 = 0; i < 2; i++) {
        if (cLib_distanceAngleS(angles[i], mAngles[i][param_2]) <= mMaxTurnStep[i][param_2]/2) {
            r25++;
        }
    }
    
    return r25 == i;
}

/* 8021AABC-8021AC6C       .text lookAtTarget__14dNpc_JntCtrl_cFPsP4cXyz4cXyzssb */
void dNpc_JntCtrl_c::lookAtTarget(s16* outY, cXyz* pDstPos, cXyz srcPos, s16 defaultY, s16 maxVel, bool param_6) {
    s16 deltaY;
    s32 maxY;
    s32 minY;
    s16 r23;
    s16 targetY;
    
    if (pDstPos) {
        cXyz delta;
        delta.x = pDstPos->x - srcPos.x;
        delta.y = pDstPos->y - srcPos.y;
        delta.z = pDstPos->z - srcPos.z;
        f32 distXZ = std::sqrtf(delta.x * delta.x + delta.z * delta.z);
        targetY = cM_atan2s(delta.x, delta.z);
        r23 = cM_atan2s(delta.y, distXZ);
    } else {
        targetY = defaultY;
        r23 = 0;
    }
    
    deltaY = targetY - (s32)*outY;
    maxY = mMaxAngles[1][1];
    maxY += mMaxAngles[0][1];
    minY = mMinAngles[1][1];
    minY += mMinAngles[0][1];
    bool r3 = move(deltaY, 1);
    if ((mbTrn || ((deltaY >= maxY || deltaY <= minY) && r3)) && !param_6) {
        mbTrn = follow(outY, targetY, maxVel, 1);
    }
    
    move(r23, 0);
}

/* 8021AC6C-8021ACA8       .text setParam__14dNpc_JntCtrl_cFsssssssss */
void dNpc_JntCtrl_c::setParam(s16 max_backbone_x, s16 max_backbone_y, s16 min_backbone_x, s16 min_backbone_y,
                              s16 max_head_x, s16 max_head_y, s16 min_head_x, s16 min_head_y,
                              s16 max_turn_step)
{
    mMaxAngles[1][0] = max_backbone_x;
    mMaxAngles[1][1] = max_backbone_y;
    mMinAngles[1][0] = min_backbone_x;
    mMinAngles[1][1] = min_backbone_y;
    mMaxAngles[0][0] = max_head_x;
    mMaxAngles[0][1] = max_head_y;
    mMinAngles[0][0] = min_head_x;
    mMinAngles[0][1] = min_head_y;
    mMaxTurnStep[1][0] = max_turn_step;
    mMaxTurnStep[1][1] = max_turn_step;
    mMaxTurnStep[0][0] = max_turn_step;
    mMaxTurnStep[0][1] = max_turn_step;
}

/* 8021ACA8-8021ACBC       .text setInfDrct__14dNpc_PathRun_cFP5dPath */
bool dNpc_PathRun_c::setInfDrct(dPath* pPath) {
    mPath = pPath;
    mCurrPointIndex = 0;

    return true;
}

/* 8021ACBC-8021AD1C       .text setInf__14dNpc_PathRun_cFUcScUc */
bool dNpc_PathRun_c::setInf(u8 pathIdx, s8 roomNo, u8 forwards) {
    bool setPath = false;

    mPath = 0;
    mbGoingForwards = forwards;
    if(pathIdx != 0xFF) {
        mPath = dPath_GetRoomPath(pathIdx, roomNo);
        mCurrPointIndex = 0;

        setPath = true;
    }

    return setPath;
}

/* 8021AD1C-8021AD58       .text nextPath__14dNpc_PathRun_cFSc */
dPath* dNpc_PathRun_c::nextPath(s8 roomNo) {
    dPath* pPath = NULL;

    if(mPath != 0) {
        pPath = dPath_GetNextRoomPath(mPath, roomNo);
    }

    return pPath;
}

/* 8021AD58-8021ADD0       .text getPoint__14dNpc_PathRun_cFUc */
cXyz dNpc_PathRun_c::getPoint(u8 pointIdx) {
    cXyz point(0.0f, 0.0f, 0.0f);

    if(mPath != 0 && pointIdx < mPath->m_num) {
        point = mPath->mpPnt[pointIdx].mPos;
    }

    return point;
}

/* 8021ADD0-8021AFA8       .text chkPointPass__14dNpc_PathRun_cF4cXyzb */
bool dNpc_PathRun_c::chkPointPass(cXyz currPos, bool goingForwards) {
    bool passed = false;
    if (mPath) {
        cXyz target;
        target.x = mPath->mpPnt[mCurrPointIndex].mPos.x;
        target.z = mPath->mpPnt[mCurrPointIndex].mPos.z;
        f32 deltaX;
        f32 deltaZ;
        if (mCurrPointIndex == 0) {
            deltaX = mPath->mpPnt[1].mPos.x - mPath->mpPnt[0].mPos.x;
            deltaZ = mPath->mpPnt[1].mPos.z - mPath->mpPnt[0].mPos.z;
        } else if (mCurrPointIndex == mPath->m_num - 1) {
            deltaX = mPath->mpPnt[mPath->m_num - 1].mPos.x - mPath->mpPnt[mPath->m_num - 2].mPos.x;
            deltaZ = mPath->mpPnt[mPath->m_num - 1].mPos.z - mPath->mpPnt[mPath->m_num - 2].mPos.z;
        } else {
            deltaX = mPath->mpPnt[mCurrPointIndex + 1].mPos.x - mPath->mpPnt[mCurrPointIndex - 1].mPos.x;
            deltaZ = mPath->mpPnt[mCurrPointIndex + 1].mPos.z - mPath->mpPnt[mCurrPointIndex - 1].mPos.z;
        }
        
        f32 f29 = cM_ssin(cM_atan2s(deltaX, deltaZ)) * (f32)0x7FFF;
        f32 f2 = cM_scos(cM_atan2s(deltaX, deltaZ)) * (f32)0x7FFF;
        f32 f3 = -(f29 * target.x + f2 * target.z);
        
        if (goingForwards) {
            passed = f29 * currPos.x + f2 * currPos.z + f3 > 0.0f;
        } else {
            passed = f29 * currPos.x + f2 * currPos.z + f3 <= 0.0f;
        }
    }
    return passed;
}

/* 8021AFA8-8021AFEC       .text incIdx__14dNpc_PathRun_cFv */
bool dNpc_PathRun_c::incIdx() {
    bool ret = true;

    if(mPath != 0) {
        mCurrPointIndex += 1;
        if(mCurrPointIndex >= mPath->m_num) {
            mCurrPointIndex = mPath->m_num - 1;
            ret = false;
        }
    }

    return ret;
}

/* 8021AFEC-8021B030       .text incIdxLoop__14dNpc_PathRun_cFv */
bool dNpc_PathRun_c::incIdxLoop() {
    bool ret = true;

    if(mPath != 0) {
        mCurrPointIndex += 1;
        if(mCurrPointIndex >= mPath->m_num) {
            mCurrPointIndex = 0;
            ret = false;
        }
    }

    return ret;
}

/* 8021B030-8021B0AC       .text incIdxAuto__14dNpc_PathRun_cFv */
bool dNpc_PathRun_c::incIdxAuto() {
    bool hitEnd = true;

    if(mPath != 0) {
        if(mPath->mLoops & 1) {
            mCurrPointIndex += 1;
            if(mCurrPointIndex >= mPath->m_num) {
                mCurrPointIndex = 0;
            }
        }
        else {
            mCurrPointIndex += 1;
            if(mCurrPointIndex >= mPath->m_num) {
                mCurrPointIndex = mPath->m_num - 1;
                hitEnd = false;
            }
        }
    }

    return hitEnd;
}

/* 8021B0AC-8021B0F0       .text decIdx__14dNpc_PathRun_cFv */
bool dNpc_PathRun_c::decIdx() {
    bool ret = true;

    if(mPath != 0) {
        mCurrPointIndex -= 1;
        if(mCurrPointIndex >= mPath->m_num) {
            mCurrPointIndex = 0;
            ret = false;
        }
    }

    return ret;
}

/* 8021B0F0-8021B134       .text decIdxLoop__14dNpc_PathRun_cFv */
bool dNpc_PathRun_c::decIdxLoop() {
    bool ret = true;

    if(mPath != 0) {
        mCurrPointIndex -= 1;
        if(mCurrPointIndex >= mPath->m_num) {
            mCurrPointIndex = mPath->m_num - 1;
            ret = false;
        }
    }

    return ret;
}

/* 8021B134-8021B1B0       .text decIdxAuto__14dNpc_PathRun_cFv */
bool dNpc_PathRun_c::decIdxAuto() {
    bool hitEnd = true;

    if(mPath != 0) {
        if(mPath->mLoops & 1) {
            mCurrPointIndex -= 1;
            if(mCurrPointIndex >= mPath->m_num) {
                mCurrPointIndex = mPath->m_num - 1;
            }
        }
        else {
            mCurrPointIndex -= 1;
            if(mCurrPointIndex >= mPath->m_num) {
                mCurrPointIndex = 0;
                hitEnd = false;
            }
        }
    }

    return hitEnd;
}

/* 8021B1B0-8021B224       .text nextIdx__14dNpc_PathRun_cFv */
bool dNpc_PathRun_c::nextIdx() {
    bool hitEnd;

    if(mbGoingForwards) {
        hitEnd = incIdx();
        if(hitEnd == false) {
            decIdx();
        }
    }
    else {
        hitEnd = decIdx();
        if(hitEnd == false) {
            incIdx();
        }
    }

    return hitEnd;
}

/* 8021B224-8021B298       .text nextIdxAuto__14dNpc_PathRun_cFv */
bool dNpc_PathRun_c::nextIdxAuto() {
    bool hitEnd;

    if(mbGoingForwards) {
        hitEnd = incIdxAuto();
        if(hitEnd == 0) {
            decIdx();
        }
    }
    else {
        hitEnd = decIdxAuto();
        if(hitEnd == 0) {
            incIdx();
        }
    }

    return hitEnd;
}

/* 8021B298-8021B328       .text absIdx__14dNpc_PathRun_cFUcUc */
s32 dNpc_PathRun_c::absIdx(u8 startIdx, u8 lastIdx) {
    if(mPath == 0) {
        return 0;
    }
    
    s32 diff_1 = startIdx - lastIdx;
    s32 diff_2 = lastIdx - startIdx;

    if(diff_1 < 0) {
        diff_1 += maxPoint();
    }
    if(diff_2 < 0) {
        diff_2 += maxPoint();
    }
    if(diff_1 > diff_2) {
        return diff_2;
    }

    return diff_1;
}

/* 8021B328-8021B348       .text maxPoint__14dNpc_PathRun_cFv */
u8 dNpc_PathRun_c::maxPoint() {
    u8 max = 0xFF;
    if(mPath != 0) {
        max = mPath->m_num;
    }

    return max;
}

/* 8021B348-8021B384       .text pointArg__14dNpc_PathRun_cFUc */
u8 dNpc_PathRun_c::pointArg(u8 idx) {
    u8 arg = 0;
    if(mPath != 0 && idx < (u8)mPath->m_num) {
        arg = mPath->mpPnt[idx].mArg3;
    }

    return arg;
}

/* 8021B384-8021B514       .text setNearPathIndx__14dNpc_PathRun_cFP4cXyzf */
bool dNpc_PathRun_c::setNearPathIndx(cXyz* param_1, f32 param_2) {
    bool set = false;
    if(mPath != 0) {
        f32 max_dist = 1000000000.0f;
        u8 pointIdx = 0;
        for(int i = 0; i < maxPoint(); i++) {
            cXyz point = getPoint(i);
    
            cXyz diff = (*param_1 - point);
            f32 xz_mag = diff.abs2XZ();
            f32 y_mag = param_2 * (diff.y * diff.y);
            f32 dist = std::sqrtf(y_mag + xz_mag);

            if(max_dist > dist) {
                max_dist = dist;
                pointIdx = i;
            }
        }

        mCurrPointIndex = pointIdx;
        set = true;
    }

    return set;
}

/* 8021B514-8021B670       .text setNearPathIndxMk__14dNpc_PathRun_cFP4cXyz */
f32 dNpc_PathRun_c::setNearPathIndxMk(cXyz* param_1) {
    f32 max_dist;
    if(mPath != 0) {
        max_dist = 1000000000.0f;
        u8 pointIdx = 0;
        for(int i = 0; i < maxPoint(); i++) {
            cXyz point = getPoint(i);
            cXyz diff = (*param_1 - point);
            f32 dist = diff.abs();
            if(max_dist > dist) {
                max_dist = dist;
                pointIdx = i;
            }
        }

        mCurrPointIndex = pointIdx;
    }

    return max_dist;
}

/* 8021B670-8021B818       .text setNearPathIndxMk2__14dNpc_PathRun_cFP4cXyzUcUc */
bool dNpc_PathRun_c::setNearPathIndxMk2(cXyz* param_1, u8 param_2, u8 param_3) {
    u8 pointIdx;
    bool set = false;
    if(mPath != 0) {
        f32 max_dist = 1000000000.0f;
        pointIdx = param_2;
        for(int i = 0; i < maxPoint(); i++) {
            cXyz point = getPoint(i);
            cXyz diff = (*param_1 - point);
            f32 dist = diff.abs();
            s32 idx = absIdx(param_2, i);
            if(idx <= param_3 && param_2 != i && max_dist > dist) {
                max_dist = dist;
                pointIdx = i;
                set = true;
            }
        }

        mCurrPointIndex = pointIdx;
    }

    return set;
}

/* 8021B818-8021B95C       .text chkInside__14dNpc_PathRun_cFP4cXyz */
bool dNpc_PathRun_c::chkInside(cXyz* param_1) {
    cXyz point, point2, point3;

    setNearPathIndx(param_1, 0.0f);
    point2 = getPoint(mCurrPointIndex);
    decIdxLoop();
    point = getPoint(mCurrPointIndex);
    incIdxLoop();
    incIdxLoop();
    point3 = getPoint(mCurrPointIndex);

    s16 angle1 = cLib_targetAngleY(&point2, &point);
    s16 angle2 = cLib_targetAngleY(&point2, param_1);
    s16 angle3 = cLib_targetAngleY(&point2, &point3);

    s16 diff1 = angle2 - angle3;
    s16 diff2 = angle1 - angle3;
    if(diff1 > 0) {
        if(diff2 < 0 || diff1 < diff2) {
            return true;
        }
    }
    else if(diff2 < 0 && diff1 < diff2) {
        return true;
    }

    return false;
}

#include "d/d_npc_event_cut.inc"

/* 8021B95C-8021B998       .text setActorInfo__15dNpc_EventCut_cFPcP10fopAc_ac_c */
void dNpc_EventCut_c::setActorInfo(char* staffName, fopAc_ac_c* pActor) {
    mpEvtStaffName = staffName;
    mpActor = pActor;
    mTargetActorPos.set(0.0f, 0.0f, 0.0f);
    mOffsetPos.set(0.0f, 0.0f, 0.0f);
    mPos.set(0.0f, 0.0f, 0.0f);
    mCurActIdx = -1;
}

/* 8021B998-8021B9D8       .text setActorInfo2__15dNpc_EventCut_cFPcP12fopNpc_npc_c */
void dNpc_EventCut_c::setActorInfo2(char* staffName, fopNpc_npc_c* pActor) {
    mpEvtStaffName = staffName;
    mpActor = pActor;
    mpTalkActor = pActor;
    mTargetActorPos.set(0.0f, 0.0f, 0.0f);
    mOffsetPos.set(0.0f, 0.0f, 0.0f);
    mPos.set(0.0f, 0.0f, 0.0f);
    mCurActIdx = -1;
}

/* 8021B9D8-8021BABC       .text dNpc_setAnmIDRes__FP14mDoExt_McaMorfiffiiPCc */
bool dNpc_setAnmIDRes(mDoExt_McaMorf* pMorf, int loopMode, float morf, float speed, int animResId, int soundResId, const char* arcName) {
    void* pSoundAnimRes = NULL;
    bool ret = false;

    if(pMorf != 0) {
        if(0 <= soundResId) {
            pSoundAnimRes = dComIfG_getObjectIDRes(arcName, soundResId);
        }

        J3DAnmTransform* pAnimRes = static_cast<J3DAnmTransform*>(dComIfG_getObjectIDRes(arcName, animResId));
        pMorf->setAnm(pAnimRes, loopMode, morf, speed, 0.0f, -1.0f, pSoundAnimRes);
        
        ret = true;
    }

    return ret;
}

/* 8021BABC-8021BBA8       .text dNpc_setAnmFNDirect__FP14mDoExt_McaMorfiffPcPcPCc */
bool dNpc_setAnmFNDirect(mDoExt_McaMorf* pMorf, int loopMode, f32 morf, f32 speed, char* animFilename, char* soundFilename, const char* arcName) {
    bool ret = false;

    if(pMorf != 0 && animFilename != 0 && arcName != 0) {
        J3DAnmTransform* pAnimRes = (J3DAnmTransform*)dComIfG_getObjectRes(arcName, animFilename);

        void* pSoundAnimRes = NULL;
        if(soundFilename != 0) {
            pSoundAnimRes = dComIfG_getObjectRes(arcName, soundFilename);
        }

        pMorf->setAnm(pAnimRes, loopMode, morf, speed, 0.0f, -1.0f, pSoundAnimRes);
        
        ret = true;
    }

    return ret;
}

/* 8021BBA8-8021BC8C       .text dNpc_setAnm__FP14mDoExt_McaMorfiffiiPCc */
bool dNpc_setAnm(mDoExt_McaMorf* pMorf, int loopMode, f32 morf, f32 speed, int animFileIdx, int soundFileIdx, const char* arcName) {
    void* pSoundAnimRes = NULL;
    bool ret = false;

    if(pMorf != 0) {
        if(0 <= soundFileIdx) {
            pSoundAnimRes = dComIfG_getObjectRes(arcName, soundFileIdx);
        }

        J3DAnmTransform* pAnimRes = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes(arcName, animFileIdx));
        pMorf->setAnm(pAnimRes, loopMode, morf, speed, 0.0f, -1.0f, pSoundAnimRes);
        
        ret = true;
    }

    return ret;
}

/* 8021BC8C-8021BD2C       .text dNpc_setShadowModel__FP8J3DModelP12J3DModelDataP8J3DModel */
void dNpc_setShadowModel(J3DModel* param_1, J3DModelData* param_2, J3DModel* param_3) {
    for(int i = 0; i < param_2->getWEvlpMtxNum(); i++) {
        mDoMtx_copy(param_3->mpWeightEnvMtx[i], param_1->mpWeightEnvMtx[i]);
    }
    for(int i = 0; i < param_2->getJointNum(); i++) {
        mDoMtx_copy(param_3->mpNodeMtx[i], param_1->mpNodeMtx[i]);
    }
}

/* 8021BD2C-8021BDE8       .text dNpc_playerEyePos__Ff */
cXyz dNpc_playerEyePos(f32 offsetY) {
    daPy_py_c* pPlayer = daPy_getPlayerActorClass();
    cXyz pos = pPlayer->getHeadTopPos();
    cXyz out;

    MtxTrans(pos.x, pos.y, pos.z, false);
    pos.set(0.0f, offsetY, 0.0f);
    MtxPosition(&pos, &out);
    
    out.x = pPlayer->current.pos.x;
    out.z = pPlayer->current.pos.z;

    return out;
}

/* 8021BDE8-8021BEC4       .text dNpc_calc_DisXZ_AngY__F4cXyz4cXyzPfPs */
void dNpc_calc_DisXZ_AngY(cXyz param_1, cXyz param_2, float* param_3, s16* param_4) {
    cXyz diff;
    diff.x = param_2.x - param_1.x;
    diff.z = param_2.z - param_1.z;

    if(param_3 != 0) {
        f32 dist = std::sqrtf(diff.x * diff.x + diff.z * diff.z);
        *param_3 = dist;
    }

    if(param_4 != 0) {
        *param_4 = cM_atan2s(diff.x, diff.z);
    }
}

/* 8021BEC4-8021BF30       .text dNpc_chkArasoi__Fv */
bool dNpc_chkArasoi() {
    return dComIfGs_isEventBit(0x1220) && !dComIfGs_isEventBit(0x1808);
}

/* 8021BF30-8021BF98       .text dNpc_chkLetterPassed__Fv */
bool dNpc_chkLetterPassed() {
    bool ret = false;
    if(dComIfGs_isGetItemReserve(0xC)) {
        ret = dComIfGs_checkReserveItem(dItem_FATHER_LETTER_e) == 0;
    }
    return ret;
}

/* 8021BF98-8021C010       .text setCollision__12fopNpc_npc_cFff */
void fopNpc_npc_c::setCollision(f32 radius, f32 height) {
    mCyl.SetC(current.pos);
    mCyl.SetR(radius);
    mCyl.SetH(height);
    dComIfG_Ccsp()->Set(&mCyl);
}

/* 8021C010-8021C120       .text talk__12fopNpc_npc_cFi */
u16 fopNpc_npc_c::talk(int param_1) {
    u16 status = 0xFF;

    if(mCurrMsgBsPcId == fpcM_ERROR_PROCESS_ID_e) {
        if(param_1 == 1) {
            mCurrMsgNo = getMsg();
        }

        mCurrMsgBsPcId = fopMsgM_messageSet(mCurrMsgNo, this);
        mpCurrMsg = NULL;
    }
    else {
        if(mpCurrMsg) {
            status = mpCurrMsg->mStatus;
            if(status == fopMsgStts_MSG_DISPLAYED_e) {
                mpCurrMsg->mStatus = next_msgStatus(&mCurrMsgNo);
                if(mpCurrMsg->mStatus == fopMsgStts_MSG_CONTINUES_e) {
                    fopMsgM_messageSet(mCurrMsgNo);
                }
            }
            else if (status == fopMsgStts_BOX_CLOSED_e) {
                mpCurrMsg->mStatus = fopMsgStts_MSG_DESTROYED_e;
                mCurrMsgBsPcId = fpcM_ERROR_PROCESS_ID_e;
            }

            anmAtr(status);
        }
        else {
            mpCurrMsg = fopMsgM_SearchByID(mCurrMsgBsPcId);
        }
    }

    return status;
}

/* 8021C120-8021C238       .text dNpc_setAnm_2__FP14mDoExt_McaMorfiffiiPCc */
bool dNpc_setAnm_2(mDoExt_McaMorf* pMorf, int loopMode, f32 morf, f32 speed, int animFileIdx, int soundFileIdx, const char* arcName) {
    if(0 <= soundFileIdx) {
        void* pSoundAnimRes = dComIfG_getObjectRes(arcName, soundFileIdx);
        J3DAnmTransform* pAnimRes = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes(arcName, animFileIdx));
        
        pMorf->setAnm(pAnimRes, loopMode, morf, speed, 0.0f, -1.0f, pSoundAnimRes);
    }
    else {
        J3DAnmTransform* pAnimRes = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes(arcName, animFileIdx));

        pMorf->setAnm(pAnimRes, loopMode, morf, speed, 0.0f, -1.0f, 0);
    }


    return true;
}

/* 8021C238-8021C2E8       .text swing_vertical_init__14dNpc_HeadAnm_cFsssi */
void dNpc_HeadAnm_c::swing_vertical_init(s16 param_1, s16 param_2, s16 param_3, int param_4) {
    if(param_4 == 0 || mFunc != &dNpc_HeadAnm_c::swing_vertical) {
        field_0x1C = 0;
        field_0x20 = param_1;
        field_0x1E = param_2;
        field_0x14 = param_3;
        mFunc = &dNpc_HeadAnm_c::swing_vertical;
    }
}

/* 8021C2E8-8021C3C8       .text swing_vertical__14dNpc_HeadAnm_cFv */
void dNpc_HeadAnm_c::swing_vertical() {
    s16 temp2 = field_0x1C;
    field_0x1C += field_0x1E;
    s16 temp = cM_ssin(field_0x1C) * field_0x14;
    cLib_addCalcAngleS(&field_0x00, temp, 4, 0x1000, 0x100);
    cLib_addCalcAngleS(&field_0x02, 0, 4, 0x1000, 0x100);
    
    if (temp2 < 0 && field_0x1C >= 0 && --field_0x20 <= 0) {
        mFunc = NULL;
    }
}

/* 8021C3C8-8021C478       .text swing_horizone_init__14dNpc_HeadAnm_cFsssi */
void dNpc_HeadAnm_c::swing_horizone_init(s16 param_1, s16 param_2, s16 param_3, int param_4) {
    if(param_4 == 0 || mFunc != &dNpc_HeadAnm_c::swing_vertical) {
        field_0x1C = 0;
        field_0x20 = param_1;
        field_0x1E = param_2;
        field_0x18 = param_3;
        mFunc = &dNpc_HeadAnm_c::swing_horizone;
    }
}

/* 8021C478-8021C55C       .text swing_horizone__14dNpc_HeadAnm_cFv */
void dNpc_HeadAnm_c::swing_horizone() {
    s16 temp2 = field_0x1C;
    field_0x1C += field_0x1E;
    s16 temp = cM_ssin(field_0x1C) * field_0x18;
    cLib_addCalcAngleS(&field_0x00, 0, 4, 0x1000, 0x100);
    cLib_addCalcAngleS(&field_0x02, temp, 4, 0x1000, 0x100);
    
    if (temp2 < 0 && field_0x1C >= 0 && --field_0x20 <= 0) {
        mFunc = NULL;
    }
}

/* 8021C55C-8021C5D8       .text move__14dNpc_HeadAnm_cFv */
void dNpc_HeadAnm_c::move() {
    if(mFunc) {
        (this->*mFunc)();
    }
    else {
        cLib_addCalcAngleS(&field_0x00, 0, 4, 0x1000, 0x100);
        cLib_addCalcAngleS(&field_0x02, 0, 4, 0x1000, 0x100);
    }
}

/* 8021C5D8-8021C620       .text chkLim__14dNpc_JntCtrl_cFsii */
int dNpc_JntCtrl_c::chkLim(s16 angle, int param_2, int param_3) {
    angle = cLib_maxLimit(angle, mMaxAngles[param_2][param_3]);
    angle = cLib_minLimit(angle, mMinAngles[param_2][param_3]);
    return angle;
}

/* 8021C620-8021C6D8       .text turn_fromBackbone2Head__14dNpc_JntCtrl_cFsPsPsb */
void dNpc_JntCtrl_c::turn_fromBackbone2Head(s16 param_1, s16* param_2, s16* param_3, bool param_4) {
    *param_3 = 0;
    if(!mbBackBoneLock) {
        *param_3 = chkLim(param_1, 1, 1);
        if(field_0x32 && *param_3 < 0) {
            *param_3 = 0;
        }
    }
    
    *param_2 = 0;
    if(!mbHeadLock) {
        *param_2 = param_1 - *param_3;
        *param_2 = chkLim(*param_2, 0, 1);
    }
}

/* 8021C6D8-8021C780       .text turn_fromHead2Backbone__14dNpc_JntCtrl_cFsPsPs */
void dNpc_JntCtrl_c::turn_fromHead2Backbone(s16 param_1, s16* param_2, s16* param_3) {
    *param_2 = 0;
    if(!mbHeadLock) {
        *param_2 = param_1 - field_0x32;
        *param_2 = chkLim(*param_2, 0, 1);
    }

    *param_3 = 0;
    if(!mbBackBoneLock) {
        *param_3 = param_1 - *param_2;
        *param_3 = chkLim(*param_3, 1, 1);
    }
}

/* 8021C780-8021C7D0       .text follow_current__14dNpc_JntCtrl_cFPss */
s16 dNpc_JntCtrl_c::follow_current(s16* pAngle, s16 diff) {
    s16 angle = *pAngle;
    *pAngle -= diff;

    s16 ret = 0;
    if((angle > 0 && *pAngle < 0) || (angle < 0 && *pAngle > 0)) {
        ret = -*pAngle;
        *pAngle = 0;
    }
    
    return ret;
}

/* 8021C7D0-8021CAB8       .text lookAtTarget_2__14dNpc_JntCtrl_cFPsP4cXyz4cXyzssb */
void dNpc_JntCtrl_c::lookAtTarget_2(s16* r26, cXyz* r29, cXyz r24, s16 r7, s16 r27, bool r28) {
    s16 targetY;
    s16 targetX;
    s32 r1_10;
    s32 temp6;
    s16 temp;
    s16 temp2;
    s32 temp4;
    s32 r1_0C;
    s16 r1_08[2];
    s16 deltaY;
    s32 temp10;
    s32 temp11;
    s32 temp5;
    int temp9;
    s32 temp7;
    
    if (r29) {
        targetY = cLib_targetAngleY(&r24, r29);
        targetX = cLib_targetAngleX(&r24, r29);
    } else {
        targetY = r7;
        targetX = 0;
    }
    
    deltaY = targetY - *r26;
    if (0 <= field_0x32) {
        if (deltaY >= field_0x32 || field_0x32 == 0) {
            turn_fromHead2Backbone(deltaY, &r1_08[1], &r1_08[0]);
        } else {
            turn_fromBackbone2Head(deltaY, &r1_08[1], &r1_08[0], 0 <= field_0x32);
        }
    } else {
        if (deltaY <= field_0x32 || field_0x32 == 0) {
            turn_fromHead2Backbone(deltaY, &r1_08[1], &r1_08[0]);
        } else {
            turn_fromBackbone2Head(deltaY, &r1_08[1], &r1_08[0], 0 <= field_0x32);
        }
    }
    
    field_0x2E = r1_08[1];
    field_0x32 = r1_08[0];
    temp10 = field_0x2E;
    temp11 = field_0x32;
    r1_10 = mAngles[0][1];
    r1_0C = mAngles[1][1];
    cLib_addCalcAngleL(&r1_10, temp10, 4, mMaxTurnStep[0][0], 4);
    cLib_addCalcAngleL(&r1_0C, temp11, 4, mMaxTurnStep[0][0], 4);
    mAngles[0][1] = r1_10;
    mAngles[1][1] = r1_0C;
    
    if (mbTrn && !r28) {
        temp = *r26;
        cLib_addCalcAngleS(r26, targetY, 4, r27, 0x100);
        temp2 = *r26 - temp;
        mbTrn = temp2 != 0;
        if (!mbBackBoneLock) {
            temp2 = follow_current(&mAngles[1][1], temp2);
        }
        if (!mbHeadLock) {
            follow_current(&mAngles[0][1], temp2);
        }
    } else {
        temp4 = field_0x2E + field_0x32;
        if (deltaY >= 0) {
            mbTrn = deltaY > temp4;
        } else {
            mbTrn = deltaY < temp4;
        }
    }
    
    temp5 = targetX;
    temp5 = chkLim(temp5, 0, 0);
    targetX = targetX - (int)temp5;
    temp9 = chkLim(targetX, 1, 0);
    field_0x2C = temp5;
    field_0x30 = temp9;
    targetX = field_0x30;
    temp7 = field_0x2C;
    temp6 = field_0x30;
    r1_10 = mAngles[0][0];
    r1_0C = mAngles[1][0];
    cLib_addCalcAngleL(&r1_10, temp7, 4, mMaxTurnStep[0][0], 4);
    cLib_addCalcAngleL(&r1_0C, temp6, 4, mMaxTurnStep[0][0], 4);
    mAngles[0][0] = r1_10;
    mAngles[1][0] = r1_0C;
}

/* 8021CAB8-8021CC4C       .text dNpc_chkAttn__FP10fopAc_ac_c4cXyzfffb */
bool dNpc_chkAttn(fopAc_ac_c* i_this, cXyz destPos, f32 param_3, f32 param_4, f32 param_5, bool param_6) {
    s16 angle = cLib_targetAngleY(&i_this->current.pos, &destPos);
    f32 dist = (i_this->current.pos - destPos).absXZ();
    f32 temp = param_3;
    s16 angle_diff = angle - i_this->current.angle.y;

    param_5 = cLib_maxLimit(param_5, 359.0f);
    param_5 = cLib_minLimit(param_5, 0.0f);
    
    if(param_6) {
        temp += param_4;
    }

    bool ret = false;
    if(dist <= temp && abs(angle_diff) <= cM_deg2s(param_5)) {
        ret = true;
    }

    return ret;
}

static void dummyfunc(dStage_dPath_c* i_pathInf) {
    JUT_ASSERT(0, i_pathInf != NULL);
}

dCcD_SrcCyl dNpc_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ ~(AT_TYPE_BOOMERANG),
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 0.0f,
        /* Height */ 0.0f,
    },
};
