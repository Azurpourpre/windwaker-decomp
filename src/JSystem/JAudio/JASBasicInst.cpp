//
// Generated by dtk
// Translation Unit: JASBasicInst.cpp
//

#include "JSystem/JAudio/JASBasicInst.h"
#include "JSystem/JAudio/JASBank.h"
#include "JSystem/JAudio/JASCalc.h"
#include "JSystem/JAudio/JASInstEffect.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JUtility/JUTAssert.h"

/* 80284844-80284888       .text __ct__Q28JASystem10TBasicInstFv */
JASystem::TBasicInst::TBasicInst() {
    field_0x4 = 1.0f;
    field_0x8 = 1.0f;
    mEffect = NULL;
    mEffectCount = 0;
    mOsc = NULL;
    mOscCount = 0;
    mKeyRegionCount = 0;
    mKeymap = NULL;
}

/* 80284888-80284914       .text __dt__Q28JASystem10TBasicInstFv */
JASystem::TBasicInst::~TBasicInst() {
    delete[] mKeymap;
    delete[] mEffect;
    delete[] mOsc;
}

/* 80284914-80284B4C       .text getParam__Q28JASystem10TBasicInstCFiiPQ28JASystem10TInstParam */
bool JASystem::TBasicInst::getParam(int key, int velo, TInstParam* param) const {
    param->field_0x0 = 0;
    param->field_0x38 = 0;
    param->mOscData = mOsc;
    param->mOscCount = mOscCount;
    param->field_0x10 *= field_0x4;
    param->field_0x14 *= field_0x8;
    for (int i = 0; i < mEffectCount; i++) {
        TInstEffect* effect = mEffect[i];
        if (!effect) {
            continue;
        }
        f32 y = effect->getY(key, velo);
        switch (effect->mTarget) {
        case 0:
            param->field_0x18 *= y;
            break;
        case 1:
            param->field_0x1c *= y;
            break;
        case 2:
            param->field_0x2c += y - 0.5;
            break;
        case 3:
            param->field_0x30 += y;
            break;
        case 4:
            param->field_0x34 += y;
            break;
        default:
            JUT_ASSERT(93, FALSE);
        }
    }
    const TKeymap* keymap = NULL;
    for (int i = 0; i < mKeyRegionCount; i++) {
        if (key <= mKeymap[i].mBaseKey) {
            keymap = &mKeymap[i];
            param->field_0x3c = i;
            break;
        }
    }
    if (!keymap) {
        return false;
    }
    for (int i = 0; i < keymap->mVeloRegionCount; i++) {
        const JASystem::TBasicInst::TVeloRegion * region = keymap->getVeloRegion(i);
        if (velo <= region->mBaseVel) {
            param->field_0x10 *= region->field_0x08;
            param->field_0x14 *= region->field_0x0c;
            param->field_0x4 = region->field_0x04;
            return true;
        }
    }
    return false;
}

/* 80284B4C-80284B54       .text getKeymapIndex__Q28JASystem10TBasicInstCFi */
int JASystem::TBasicInst::getKeymapIndex(int index) const {
    return index;
}

/* 80284B54-80284C10       .text setKeyRegionCount__Q28JASystem10TBasicInstFUl */
void JASystem::TBasicInst::setKeyRegionCount(u32 num) {
    delete[] mKeymap;
    mKeymap = new (TBank::getCurrentHeap(), 0) TKeymap[num];
    JUT_ASSERT(140, mKeymap != 0);
    mKeyRegionCount = num;
}

/* 80284C10-80284CC4       .text setEffectCount__Q28JASystem10TBasicInstFUl */
void JASystem::TBasicInst::setEffectCount(u32 num) {
    delete[] mEffect;
    mEffectCount = num;
    if (num == 0) {
        mEffect = NULL;
        return;
    }
    mEffect = new (TBank::getCurrentHeap(), 0) TInstEffect*[num];
    JUT_ASSERT(157, mEffect != 0);
    Calc::bzero(mEffect, num * 4);
}

/* 80284CC4-80284D7C       .text setEffect__Q28JASystem10TBasicInstFiPQ28JASystem11TInstEffect */
void JASystem::TBasicInst::setEffect(int index, TInstEffect* effect) {
    JUT_ASSERT(164, index < mEffectCount);
    JUT_ASSERT(165, index >= 0);
    mEffect[index] = effect;
}

/* 80284D7C-80284E30       .text setOscCount__Q28JASystem10TBasicInstFUl */
void JASystem::TBasicInst::setOscCount(u32 num) {
    delete[] mOsc;
    mOscCount = num;
    if (num == 0) {
        mOsc = NULL;
        return;
    }
    mOsc = new (TBank::getCurrentHeap(), 0) TOscillator::Osc_*[num];
    JUT_ASSERT(193, mOsc != 0);
    Calc::bzero(mOsc, num * 4);
}

/* 80284E30-80284EE8       .text setOsc__Q28JASystem10TBasicInstFiPQ38JASystem11TOscillator4Osc_ */
void JASystem::TBasicInst::setOsc(int index, TOscillator::Osc_* osc) {
    JUT_ASSERT(199, index < mOscCount);
    JUT_ASSERT(200, index >= 0);
    mOsc[index] = osc;
}

/* 80284EE8-80284F70       .text getKeyRegion__Q28JASystem10TBasicInstFi */
JASystem::TBasicInst::TKeymap* JASystem::TBasicInst::getKeyRegion(int index) {
    JUT_ASSERT(217, index >= 0);
    if (index >= mKeyRegionCount) {
        return NULL;
    }
    return &mKeymap[index];
}

/* 80284F70-80284FC4       .text __dt__Q38JASystem10TBasicInst7TKeymapFv */
JASystem::TBasicInst::TKeymap::~TKeymap() {
    delete[] mVelomap;
}

/* 80284FC4-80285058       .text setVeloRegionCount__Q38JASystem10TBasicInst7TKeymapFUl */
void JASystem::TBasicInst::TKeymap::setVeloRegionCount(u32 num) {
    delete[] mVelomap;
    mVelomap = new (TBank::getCurrentHeap(), 0) JASystem::TBasicInst::TVeloRegion[num];
    JUT_ASSERT(244, mVelomap != 0);
    mVeloRegionCount = num;
}

/* 80285058-802850E0       .text getVeloRegion__Q38JASystem10TBasicInst7TKeymapFi */
JASystem::TBasicInst::TVeloRegion* JASystem::TBasicInst::TKeymap::getVeloRegion(int index) {
    JUT_ASSERT(252, index >= 0);
    if (index >= mVeloRegionCount) {
        return NULL;
    }
    return &mVelomap[index];
}

/* 802850E0-80285168       .text getVeloRegion__Q38JASystem10TBasicInst7TKeymapCFi */
const JASystem::TBasicInst::TVeloRegion* JASystem::TBasicInst::TKeymap::getVeloRegion(int index) const {
    JUT_ASSERT(261, index >= 0);
    if (index >= mVeloRegionCount) {
        return NULL;
    }
    return &mVelomap[index];
}
