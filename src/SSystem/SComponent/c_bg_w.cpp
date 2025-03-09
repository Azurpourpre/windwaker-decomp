//
// Generated by dtk
// Translation Unit: c_bg_w.cpp
//

#include "SSystem/SComponent/c_bg_w.h"
#include "SSystem/SComponent/c_bg_s_gnd_chk.h"
#include "SSystem/SComponent/c_bg_s_lin_chk.h"
#include "SSystem/SComponent/c_bg_s_shdw_draw.h"
#include "SSystem/SComponent/c_m3d_g_tri.h"
#include "SSystem/SComponent/c_math.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "m_Do/m_Do_printf.h"
#include "m_Do/m_Do_mtx.h"
#include "dolphin/mtx/mtxvec.h"
#include "dolphin/types.h"

/* 80247500-8024754C       .text ASSERT_SOLDHEAP__Fv */
void ASSERT_SOLDHEAP() {
    if (JKRHeap::sCurrentHeap->getHeapType() != 'SLID')
        OSReport_Error("＊＊＊＊＊＊＊Ａバグです＊＊＊＊＊＊＊\n＊＊＊＊＊＊＊Ａバグです＊＊＊＊＊＊＊\n＊＊＊＊＊＊＊Ａバグです＊＊＊＊＊＊＊\ncBgWはカレントヒープがソリッドヒープ以外だと破綻します。\n必ず、カレントヒープをソリッドヒープにしてください。\nここでnewされた領域は二度と開放されることはありません。\n慢性的にメモリーリークを繰り返し、いずれ確実にＡバグを引き起こすことでしょう。\n必ずp修正してください。この下の水色のメッセージにアクターの名前が書いてあるはずです。\n");
}

/* 8024754C-8024760C       .text __ct__4cBgWFv */
cBgW::cBgW() {
    pm_bgd = NULL;
    mFlags = GLOBAL_e;
    mbNeedsFullTransform = true;
    mMoveCounter = 0;
    mTransVel.setall(0.0f);
    pm_tri = NULL;
    pm_rwg = NULL;
    pm_blk = NULL;
    m_nt_tbl = NULL;
    pm_grp = NULL;
    pm_vtx_tbl = NULL;
    pm_base = NULL;
    mDoMtx_identity(mOldMtx);
    mDoMtx_identity(mCurMtx);
    m_rootGrpIdx = 0xFFFF;
    mWallCorrectPriority = 2;
    mIgnorePlaneType = 0;
}

/* 8024760C-8024767C       .text __dt__4cBgWFv */
cBgW::~cBgW() {
    FreeArea();
}

/* 8024767C-8024769C       .text FreeArea__4cBgWFv */
void cBgW::FreeArea() {
    pm_tri = NULL;
    pm_rwg = NULL;
    m_nt_tbl = NULL;
    pm_blk = NULL;
    pm_grp = NULL;
    pm_vtx_tbl = NULL;
}

/* 8024769C-8024775C       .text GlobalVtx__4cBgWFv */
void cBgW::GlobalVtx() {
    if (pm_base != NULL) {
        if (!mbNeedsFullTransform) {
            for (s32 i = 0; i < pm_bgd->m_v_num; i++)
                VECAdd(&pm_vtx_tbl[i], &mTransVel, &pm_vtx_tbl[i]);
        } else {
            for (s32 i = 0; i < pm_bgd->m_v_num; i++)
                MTXMultVec(*pm_base, &pm_bgd->m_v_tbl[i], &pm_vtx_tbl[i]);
        }
    }
}

/* 8024775C-80247840       .text SetVtx__4cBgWFv */
bool cBgW::SetVtx() {
    ASSERT_SOLDHEAP();
    if (mFlags & NO_VTX_TBL_e) {
        pm_vtx_tbl = NULL;
    } else {
        if (ChkMoveBg()) {
            pm_vtx_tbl = (cBgD_Vtx_t*)new Vec[pm_bgd->m_v_num];
            if (pm_vtx_tbl == NULL)
                return true;

            if (mFlags & UNK40_e) {
                for (s32 i = 0; i < pm_bgd->m_v_num; i++) {
                    pm_vtx_tbl[i].x = 0.0f;
                    pm_vtx_tbl[i].y = 0.0f;
                    pm_vtx_tbl[i].z = 0.0f;
                }
            }
            GlobalVtx();
        } else {
            pm_vtx_tbl = pm_bgd->m_v_tbl;
        }
    }

    return false;
}

/* 80247840-80247944       .text CalcPlane__4cBgWFv */
void cBgW::CalcPlane() {
    const cBgD_Tri_t* t_tbl = pm_bgd->m_t_tbl;

    if (pm_vtx_tbl == NULL)
        return;

    if (!mbNeedsFullTransform) {
        for (s32 i = 0; i < pm_bgd->m_t_num; i++) {
            f32 dot = VECDotProduct(pm_tri[i].m_plane.GetNP(), &mTransVel);
            pm_tri[i].m_plane.mD -= dot;
        }
    } else {
        for (s32 i = 0; i < pm_bgd->m_t_num; i++) {
            cBgW_TriElm* tri_elm = &pm_tri[i];
            cM3d_CalcPla(&pm_vtx_tbl[t_tbl[i].vtx0], &pm_vtx_tbl[t_tbl[i].vtx1], &pm_vtx_tbl[t_tbl[i].vtx2], tri_elm->m_plane.GetNP(), &tri_elm->m_plane.mD);
        }
    }
}

/* 80247944-802479D8       .text SetTri__4cBgWFv */
bool cBgW::SetTri() {
    ASSERT_SOLDHEAP();
    pm_tri = new cBgW_TriElm[pm_bgd->m_t_num];
    if (pm_tri == NULL)
        return true;
    CalcPlane();
    return false;
}

/* 802479D8-80247A24       .text BlckConnect__4cBgWFPUsPii */
void cBgW::BlckConnect(u16* rwg, int* prev, int i_no) {
    if (*rwg == 0xFFFF)
        *rwg = i_no;
    if (*prev != 0xFFFF)
        pm_rwg[*prev].next = i_no;
    *prev = i_no;
    pm_rwg[*prev].next = -1;
}

inline bool cBgW_CheckBGround(f32 ny) {
    return ny >= 0.5f;
}

inline bool cBgW_CheckBRoof(f32 ny) {
    return ny < (-4.0f / 5.0f);
}

/* 80247A24-80247BF8       .text ClassifyPlane__4cBgWFv */
void cBgW::ClassifyPlane() {
    if (pm_vtx_tbl == NULL)
        return;

    s32 i = 0;

    int roof, wall, ground;
    for (; i < pm_bgd->m_b_num; i++) {
        s32 startTri = pm_bgd->m_b_tbl[i].startTri;
        s32 lastTri;
        if (i != pm_bgd->m_b_num - 1)
            lastTri = pm_bgd->m_b_tbl[i + 1].startTri - 1;
        else
            lastTri = pm_bgd->m_t_num - 1;

        pm_blk[i].roof = 0xFFFF;
        pm_blk[i].wall = 0xFFFF;
        pm_blk[i].ground = 0xFFFF;

        ground = 0xFFFF;
        wall = 0xFFFF;
        roof = 0xFFFF;

        for (s32 j = startTri; j <= lastTri; j++) {
            cBgW_TriElm* tri_elm = &pm_tri[j];

            f32 ny = tri_elm->m_plane.GetNP()->y;
            if (cM3d_IsZero(tri_elm->m_plane.GetNP()->x) && cM3d_IsZero(tri_elm->m_plane.GetNP()->y) && cM3d_IsZero(tri_elm->m_plane.GetNP()->z))
                continue;

            if (cBgW_CheckBGround(ny)) {
                if (!(mIgnorePlaneType & 1))
                    BlckConnect(&pm_blk[i].ground, &ground, j);
            } else if (cBgW_CheckBRoof(ny)) {
                if (!(mIgnorePlaneType & 4))
                    BlckConnect(&pm_blk[i].roof, &roof, j);
            } else {
                if (!(mIgnorePlaneType & 2))
                    BlckConnect(&pm_blk[i].wall, &wall, j);
            }
        }
    }
}

/* 80247BF8-80247C4C       .text MakeBlckTransMinMax__4cBgWFP4cXyzP4cXyz */
void cBgW::MakeBlckTransMinMax(cXyz* min, cXyz* max) {
    VECAdd(min, &mTransVel, min);
    VECAdd(max, &mTransVel, max);
}

/* 80247C4C-80247CD4       .text MakeBlckMinMax__4cBgWFiP4cXyzP4cXyz */
void cBgW::MakeBlckMinMax(int i_no, cXyz* min, cXyz* max) {
    Vec* vtx = &pm_vtx_tbl[i_no];
    if (min->x > vtx->x) min->x = vtx->x;
    if (max->x < vtx->x) max->x = vtx->x;
    if (min->y > vtx->y) min->y = vtx->y;
    if (max->y < vtx->y) max->y = vtx->y;
    if (min->z > vtx->z) min->z = vtx->z;
    if (max->z < vtx->z) max->z = vtx->z;
}

/* 80247CD4-80247E48       .text MakeBlckBnd__4cBgWFiP4cXyzP4cXyz */
void cBgW::MakeBlckBnd(int i, cXyz* min, cXyz* max) {
    s32 startTri = pm_bgd->m_b_tbl[i].startTri;
    s32 lastTri = (i != pm_bgd->m_b_num - 1) ? pm_bgd->m_b_tbl[i + 1].startTri - 1 : pm_bgd->m_t_num - 1;

    if (!mbNeedsFullTransform) {
        MakeBlckTransMinMax(min, max);
    } else {
        min->x = min->y = min->z = 1000000000.0f;
        max->x = max->y = max->z = -1000000000.0f;

        for (s32 j = startTri; j <= lastTri; j++) {
            MakeBlckMinMax(pm_bgd->m_t_tbl[j].vtx0, min, max);
            MakeBlckMinMax(pm_bgd->m_t_tbl[j].vtx1, min, max);
            MakeBlckMinMax(pm_bgd->m_t_tbl[j].vtx2, min, max);
        }

        min->x -= 1.0f;
        min->y -= 1.0f;
        min->z -= 1.0f;
        max->x += 1.0f;
        max->y += 1.0f;
        max->z += 1.0f;
    }
}

/* 80247E48-80247F4C       .text MakeNodeTreeRp__4cBgWFi */
void cBgW::MakeNodeTreeRp(int i) {
    const cBgD_Tree_t* tree = &pm_bgd->m_tree_tbl[i];
    if (tree->mFlag & 1) {
        // leaf
        s32 block = tree->mBlock;
        if (block != 0xFFFF) {
            MakeBlckBnd(tree->mBlock, m_nt_tbl[i].GetMinP(), m_nt_tbl[i].GetMaxP());
        }
    } else {
        // branch
        m_nt_tbl[i].ClearForMinMax();
        for (s32 j = 0; j < 8; j++) {
            s32 child = tree->mChild[j];
            if (child == 0xFFFF)
                continue;
            MakeNodeTreeRp(child);
            m_nt_tbl[i].SetMinMax(*m_nt_tbl[child].GetMinP());
            m_nt_tbl[i].SetMinMax(*m_nt_tbl[child].GetMaxP());
        }
    }
}

/* 80247F4C-80248078       .text MakeNodeTreeGrpRp__4cBgWFi */
void cBgW::MakeNodeTreeGrpRp(int grp_id) {
    u32 tree_idx = pm_bgd->m_g_tbl[grp_id].m_tree_idx;
    if (tree_idx != 0xFFFF) {
        MakeNodeTreeRp(tree_idx);
        pm_grp[grp_id].aab.SetMin(*m_nt_tbl[pm_bgd->m_g_tbl[grp_id].m_tree_idx].GetMinP());
        pm_grp[grp_id].aab.SetMax(*m_nt_tbl[pm_bgd->m_g_tbl[grp_id].m_tree_idx].GetMaxP());
    }

    s32 child_idx = pm_bgd->m_g_tbl[grp_id].m_first_child;
    while (true) {
        if (child_idx == 0xFFFF)
            break;
        MakeNodeTreeGrpRp(child_idx);
        pm_grp[grp_id].aab.SetMin(*pm_grp[child_idx].aab.GetMinP());
        pm_grp[grp_id].aab.SetMax(*pm_grp[child_idx].aab.GetMaxP());
        child_idx = pm_bgd->m_g_tbl[child_idx].m_next_sibling;
    }
}

/* 80248078-80248178       .text MakeNodeTree__4cBgWFv */
void cBgW::MakeNodeTree() {
    if (pm_vtx_tbl == NULL) {
        for (s32 i = 0; i < pm_bgd->m_g_num; i++) {
            if (pm_bgd->m_g_tbl[i].m_parent == 0xFFFF) {
                m_rootGrpIdx = i;
                break;
            }
        }
    } else {
        for (s32 i = 0; i < pm_bgd->m_g_num; i++) {
            pm_grp[i].aab.ClearForMinMax();
        }

        for (s32 i = 0; i < pm_bgd->m_g_num; i++) {
            if (pm_bgd->m_g_tbl[i].m_parent == 0xFFFF) {
                m_rootGrpIdx = i;
                MakeNodeTreeGrpRp(i);
                break;
            }
        }
    }
}

/* 80248178-802481C4       .text ChkMemoryError__4cBgWFv */
bool cBgW::ChkMemoryError() {
    if (pm_tri == NULL || pm_rwg == NULL || pm_blk == NULL || m_nt_tbl == NULL || pm_grp == NULL)
        return true;
    return false;
}

/* 802481C4-80248414       .text Set__4cBgWFP6cBgD_tUlPA3_A4_f */
bool cBgW::Set(cBgD_t* bgd, u32 flag, Mtx* mtx) {
    ASSERT_SOLDHEAP();
    mFlags = GLOBAL_e;
    pm_vtx_tbl = NULL;
    pm_tri = NULL;
    pm_rwg = NULL;
    pm_blk = NULL;
    m_nt_tbl = NULL;
    pm_grp = NULL;
    mMoveCounter = cM_rndF(128.0f);
    if (bgd == NULL)
        return true;

    mFlags = flag;
    if (mFlags & GLOBAL_e) {
        pm_base = NULL;
        mDoMtx_identity(mOldMtx);
        mDoMtx_identity(mCurMtx);
    } else {
        pm_base = mtx;
        mDoMtx_copy(*pm_base, mOldMtx);
        mDoMtx_copy(*pm_base, mCurMtx);
    }

    pm_bgd = bgd;
    if (SetVtx() || SetTri()) {
        FreeArea();
        return true;
    }

    pm_rwg = new cBgW_RwgElm[pm_bgd->m_t_num];
    if (pm_rwg == NULL) {
        FreeArea();
        return true;
    }

    pm_blk = new cBgW_BlkElm[pm_bgd->m_b_num];
    if (pm_blk == NULL) {
        FreeArea();
        return true;
    }

    m_nt_tbl = new cBgW_NodeTree[pm_bgd->m_tree_num];
    if (m_nt_tbl == NULL) {
        FreeArea();
        return true;
    }

    pm_grp = new cBgW_GrpElm[pm_bgd->m_g_num];
    if (pm_grp == NULL) {
        FreeArea();
        return true;
    }

    ClassifyPlane();
    mbNeedsFullTransform = true;
    MakeNodeTree();
    return false;
}

/* 80248414-802485FC       .text RwgLineCheck__4cBgWFUsP11cBgS_LinChk */
bool cBgW::RwgLineCheck(u16 poly_index, cBgS_LinChk* chk) {
    bool ret = false;
    cM3dGTri gtri;

    cM3dGLin *lin = chk->GetLinP();
    while (true) {
        cBgW_TriElm* tri_elm;
        cBgD_Tri_t* tri;

        tri = &pm_bgd->m_t_tbl[poly_index];
        tri_elm = &pm_tri[poly_index];

        gtri.setBg(&pm_vtx_tbl[tri->vtx0], &pm_vtx_tbl[tri->vtx1], &pm_vtx_tbl[tri->vtx2], &tri_elm->m_plane);
        bool backFlag = chk->ChkBackFlag();
        bool frontFlag = chk->ChkFrontFlag();

        cXyz pt;
        if (cM3d_Cross_LinTri(lin, &gtri, &pt, frontFlag, backFlag) && !ChkPolyThrough(poly_index, chk->GetPolyPassChk())) {
            chk->GetLinP()->SetEnd(pt);
            chk->SetPolyIndex(poly_index);
            ret = true;
        }

        if (pm_rwg[poly_index].next == 0xFFFF)
            break;

        poly_index = pm_rwg[poly_index].next;
    }

    return ret;
}

static void dummy() {
    // 0 <= bg_index
    cBgS_PolyInfo pi;
    pi.SetActorInfo(-1, NULL, 0);
}

/* 802485FC-80248868       .text LineCheckRp__4cBgWFP11cBgS_LinChki */
bool cBgW::LineCheckRp(cBgS_LinChk* chk, int i) {
    cBgW_NodeTree* node = &m_nt_tbl[i];
    if (!cM3d_Cross_MinMaxBoxLine(node->GetMinP(), node->GetMaxP(), chk->GetLinP()->GetStartP(), chk->GetLinP()->GetEndP()))
        return false;

    cBgD_Tree_t* tree = &pm_bgd->m_tree_tbl[i];
    bool ret = false;
    if (tree->mFlag & 1) {
        if (chk->mPreWallChk && pm_blk[tree->mBlock].wall != 0xFFFF && RwgLineCheck(pm_blk[tree->mBlock].wall, chk))
            ret = true;
        if (chk->mPreGroundChk && pm_blk[tree->mBlock].ground != 0xFFFF && RwgLineCheck(pm_blk[tree->mBlock].ground, chk))
            ret = true;
        if (chk->mPreRoofChk && pm_blk[tree->mBlock].roof != 0xFFFF && RwgLineCheck(pm_blk[tree->mBlock].roof, chk))
            ret = true;
        return ret;
    } else {
        // was this manually unrolled?
        if (tree->mChild[0] != 0xFFFF && LineCheckRp(chk, tree->mChild[0]))
            ret = true;
        if (tree->mChild[1] != 0xFFFF && LineCheckRp(chk, tree->mChild[1]))
            ret = true;
        if (tree->mChild[2] != 0xFFFF && LineCheckRp(chk, tree->mChild[2]))
            ret = true;
        if (tree->mChild[3] != 0xFFFF && LineCheckRp(chk, tree->mChild[3]))
            ret = true;
        if (tree->mChild[4] != 0xFFFF && LineCheckRp(chk, tree->mChild[4]))
            ret = true;
        if (tree->mChild[5] != 0xFFFF && LineCheckRp(chk, tree->mChild[5]))
            ret = true;
        if (tree->mChild[6] != 0xFFFF && LineCheckRp(chk, tree->mChild[6]))
            ret = true;
        if (tree->mChild[7] != 0xFFFF && LineCheckRp(chk, tree->mChild[7]))
            ret = true;
        return ret;
    }
}

/* 80248868-8024898C       .text LineCheckGrpRp__4cBgWFP11cBgS_LinChkii */
bool cBgW::LineCheckGrpRp(cBgS_LinChk* chk, int grp_id, int depth) {
    if (ChkGrpThrough(grp_id, chk->GetGrpPassChk(), depth))
        return false;

    if (!pm_grp[grp_id].aab.Cross(chk->GetLinP()))
        return false;

    bool ret = false;
    u16 tree = pm_bgd->m_g_tbl[grp_id].m_tree_idx;
    if (tree != 0xFFFF && LineCheckRp(chk, tree))
        ret = true;

    s32 child_idx = pm_bgd->m_g_tbl[grp_id].m_first_child;
    while (true) {
        if (child_idx == 0xFFFF)
            break;
        if (LineCheckGrpRp(chk, child_idx, depth + 1))
            ret = true;
        child_idx = pm_bgd->m_g_tbl[child_idx].m_next_sibling;
    }

    return ret;
}

/* 8024898C-80248AB8       .text RwgGroundCheckCommon__4cBgWFfUsP11cBgS_GndChk */
bool cBgW::RwgGroundCheckCommon(f32 y, u16 poly_index, cBgS_GndChk* chk) {
    if (y < chk->GetPointP()->y && y > chk->GetNowY()) {
        cBgD_Tri_t* tri = &pm_bgd->m_t_tbl[poly_index];
        if (cM3d_CrossY_Tri_Front(pm_vtx_tbl[tri->vtx0], pm_vtx_tbl[tri->vtx1], pm_vtx_tbl[tri->vtx2], &chk->m_pos) && !ChkPolyThrough(poly_index, chk->GetPolyPassChk())) {
            chk->SetNowY(y);
            chk->SetPolyIndex(poly_index);
            return true;
        }
    }

    return false;
}

/* 80248AB8-80248B68       .text RwgGroundCheckGnd__4cBgWFUsP11cBgS_GndChk */
bool cBgW::RwgGroundCheckGnd(u16 poly_index, cBgS_GndChk* chk) {
    bool ret = false;
    while (true) {
        cBgW_RwgElm* rwg = &pm_rwg[poly_index];
        cBgW_TriElm* tri = &pm_tri[poly_index];
        f32 y = tri->m_plane.getCrossY_NonIsZero(*chk->GetPointP());
        if (RwgGroundCheckCommon(y, (u16)poly_index, chk))
            ret = true;
        if (rwg->next == 0xFFFF)
            break;
        poly_index = rwg->next;
    }
    return ret;
}

/* 80248B68-80248C38       .text RwgGroundCheckWall__4cBgWFUsP11cBgS_GndChk */
bool cBgW::RwgGroundCheckWall(u16 poly_index, cBgS_GndChk* chk) {
    bool ret = false;
    while (true) {
        cBgW_TriElm* tri = &pm_tri[poly_index];
        cBgW_RwgElm* rwg = &pm_rwg[poly_index];
        if (tri->m_plane.mNormal.y >= 0.014f && RwgGroundCheckCommon(tri->m_plane.getCrossY_NonIsZero(*chk->GetPointP()), (u16)poly_index, chk))
            ret = true;
        if (rwg->next == 0xFFFF)
            break;
        poly_index = rwg->next;
    }
    return ret;
}

/* 80248C38-802491F4       .text GroundCrossRp__4cBgWFP11cBgS_GndChki */
bool cBgW::GroundCrossRp(cBgS_GndChk* chk, int i) {
    bool ret = false;
    cBgD_Tree_t* tree = &pm_bgd->m_tree_tbl[i];
    if (tree->mFlag & 1) {
        if (chk->GetGndPrecheck() && pm_blk[tree->mBlock].ground != 0xFFFF && RwgGroundCheckGnd(pm_blk[tree->mBlock].ground, chk))
            ret = true;
        if (chk->GetWallPrecheck() && pm_blk[tree->mBlock].wall != 0xFFFF && RwgGroundCheckWall(pm_blk[tree->mBlock].wall, chk))
            ret = true;
        return ret;
    } else {
        if (tree->mChild[2] != 0xFFFF) {
            cBgW_NodeTree* node = &m_nt_tbl[tree->mChild[2]];
            if (node->CrossY(chk->GetPointP()) && node->UnderPlaneYUnder(chk->GetPointP()->y) && !node->TopPlaneYUnder(chk->mNowY) && GroundCrossRp(chk, tree->mChild[2]))
                ret = true;
        }

        if (tree->mChild[3] != 0xFFFF) {
            cBgW_NodeTree* node = &m_nt_tbl[tree->mChild[3]];
            if (node->CrossY(chk->GetPointP()) && node->UnderPlaneYUnder(chk->GetPointP()->y) && !node->TopPlaneYUnder(chk->mNowY) && GroundCrossRp(chk, tree->mChild[3]))
                ret = true;
        }

        if (tree->mChild[6] != 0xFFFF) {
            cBgW_NodeTree* node = &m_nt_tbl[tree->mChild[6]];
            if (node->CrossY(chk->GetPointP()) && node->UnderPlaneYUnder(chk->GetPointP()->y) && !node->TopPlaneYUnder(chk->mNowY) && GroundCrossRp(chk, tree->mChild[6]))
                ret = true;
        }

        if (tree->mChild[7] != 0xFFFF) {
            cBgW_NodeTree* node = &m_nt_tbl[tree->mChild[7]];
            if (node->CrossY(chk->GetPointP()) && node->UnderPlaneYUnder(chk->GetPointP()->y) && !node->TopPlaneYUnder(chk->mNowY) && GroundCrossRp(chk, tree->mChild[7]))
                ret = true;
        }

        if (tree->mChild[0] != 0xFFFF) {
            cBgW_NodeTree* node = &m_nt_tbl[tree->mChild[0]];
            if (node->CrossY(chk->GetPointP()) && node->UnderPlaneYUnder(chk->GetPointP()->y) && !node->TopPlaneYUnder(chk->mNowY) && GroundCrossRp(chk, tree->mChild[0]))
                ret = true;
        }

        if (tree->mChild[1] != 0xFFFF) {
            cBgW_NodeTree* node = &m_nt_tbl[tree->mChild[1]];
            if (node->CrossY(chk->GetPointP()) && node->UnderPlaneYUnder(chk->GetPointP()->y) && !node->TopPlaneYUnder(chk->mNowY) && GroundCrossRp(chk, tree->mChild[1]))
                ret = true;
        }

        if (tree->mChild[4] != 0xFFFF) {
            cBgW_NodeTree* node = &m_nt_tbl[tree->mChild[4]];
            if (node->CrossY(chk->GetPointP()) && node->UnderPlaneYUnder(chk->GetPointP()->y) && !node->TopPlaneYUnder(chk->mNowY) && GroundCrossRp(chk, tree->mChild[4]))
                ret = true;
        }

        if (tree->mChild[5] != 0xFFFF) {
            cBgW_NodeTree* node = &m_nt_tbl[tree->mChild[5]];
            if (node->CrossY(chk->GetPointP()) && node->UnderPlaneYUnder(chk->GetPointP()->y) && !node->TopPlaneYUnder(chk->mNowY) && GroundCrossRp(chk, tree->mChild[5]))
                ret = true;
        }

        return ret;
    }
}

/* 802491F4-80249368       .text GroundCrossGrpRp__4cBgWFP11cBgS_GndChkii */
bool cBgW::GroundCrossGrpRp(cBgS_GndChk* chk, int grp_id, int depth) {
    if (ChkGrpThrough(grp_id, chk->GetGrpPassChk(), depth))
        return false;

    cBgW_GrpElm* grp = &pm_grp[grp_id];

    if (!grp->aab.CrossY(chk->GetPointP()) || !grp->aab.UnderPlaneYUnder(chk->GetPointP()->y) || grp->aab.TopPlaneYUnder(chk->mNowY))
        return false;

    bool ret = false;
    u32 tree_idx = pm_bgd->m_g_tbl[grp_id].m_tree_idx;
    if (tree_idx != 0xFFFF && GroundCrossRp(chk, tree_idx))
        ret = true;

    s32 child_idx = pm_bgd->m_g_tbl[grp_id].m_first_child;
    while (true) {
        if (child_idx == 0xFFFF)
            break;
        if (GroundCrossGrpRp(chk, child_idx, depth + 1))
            ret = true;
        child_idx = pm_bgd->m_g_tbl[child_idx].m_next_sibling;
    }

    return ret;
}

/* 80249368-802493B4       .text CopyOldMtx__4cBgWFv */
void cBgW::CopyOldMtx() {
    if (pm_base != NULL) {
        MTXCopy(mCurMtx, mOldMtx);
        MTXCopy(*pm_base, mCurMtx);
    }
}

/* 802493B4-80249584       .text Move__4cBgWFv */
void cBgW::Move() {
    if (!ChkLock() && ChkMoveBg()) {
        if (!ChkNoCalcVtx()) {
            if (mMoveCounter >= 0xFF ||
                    mCurMtx[0][0] != (*pm_base)[0][0] || mCurMtx[0][1] != (*pm_base)[0][1] || mCurMtx[0][2] != (*pm_base)[0][2] ||
                    mCurMtx[1][0] != (*pm_base)[1][0] || mCurMtx[1][1] != (*pm_base)[1][1] || mCurMtx[1][2] != (*pm_base)[1][2] ||
                    mCurMtx[2][0] != (*pm_base)[2][0] || mCurMtx[2][1] != (*pm_base)[2][1] || mCurMtx[2][2] != (*pm_base)[2][2]) {
                mbNeedsFullTransform = true;
            } else if (mCurMtx[0][3] == (*pm_base)[0][3] && mCurMtx[1][3] == (*pm_base)[1][3] && mCurMtx[2][3] == (*pm_base)[2][3]) {
                mDoMtx_copy(*pm_base, mOldMtx);
                if (!ChkFlush())
                    return;
            } else {
                mTransVel.x = (*pm_base)[0][3] - mCurMtx[0][3];
                mTransVel.y = (*pm_base)[1][3] - mCurMtx[1][3];
                mTransVel.z = (*pm_base)[2][3] - mCurMtx[2][3];
                mbNeedsFullTransform = false;
            }

            if (mMoveCounter >= 0xFF) {
                mMoveCounter = 0;
            } else {
                mMoveCounter++;
            }

            GlobalVtx();
        }

        CopyOldMtx();
        CalcPlane();
        ClassifyPlane();
        MakeNodeTree();
    }
}

/* 80249584-80249698       .text RwgShdwDraw__4cBgWFiP13cBgS_ShdwDraw */
void cBgW::RwgShdwDraw(int index, cBgS_ShdwDraw* shdw) {
    while (true) {
        cBgW_RwgElm* rwg = &pm_rwg[index];
        if (!ChkShdwDrawThrough(index, shdw->GetPolyPassChk())) {
            const cBgD_Tri_t* tri = &pm_bgd->m_t_tbl[index];
            shdw->mCallbackFun(shdw, (cBgD_Vtx_t*)pm_vtx_tbl, tri->vtx0, tri->vtx1, tri->vtx2, &pm_tri[index].m_plane);
        }
        if (rwg->next == 0xFFFF)
            break;
        index = rwg->next;
        JUT_ASSERT(0xbc6, 0 <= index && index < pm_bgd->m_t_num);
    }
}

/* 80249698-80249840       .text ShdwDrawRp__4cBgWFP13cBgS_ShdwDrawi */
void cBgW::ShdwDrawRp(cBgS_ShdwDraw* shdw, int i) {
    if (!m_nt_tbl[i].Cross(shdw->GetBndP()))
        return;

    cBgD_Tree_t* tree = &pm_bgd->m_tree_tbl[i];
    if (tree->mFlag & 1) {
        if (pm_blk[tree->mBlock].wall != 0xFFFF)
            RwgShdwDraw(pm_blk[tree->mBlock].wall, shdw);
        if (pm_blk[tree->mBlock].roof != 0xFFFF)
            RwgShdwDraw(pm_blk[tree->mBlock].roof, shdw);
        if (pm_blk[tree->mBlock].ground != 0xFFFF)
            RwgShdwDraw(pm_blk[tree->mBlock].ground, shdw);
    } else {
        if (tree->mChild[0] != 0xFFFF)
            ShdwDrawRp(shdw, tree->mChild[0]);
        if (tree->mChild[1] != 0xFFFF)
            ShdwDrawRp(shdw, tree->mChild[1]);
        if (tree->mChild[2] != 0xFFFF)
            ShdwDrawRp(shdw, tree->mChild[2]);
        if (tree->mChild[3] != 0xFFFF)
            ShdwDrawRp(shdw, tree->mChild[3]);
        if (tree->mChild[4] != 0xFFFF)
            ShdwDrawRp(shdw, tree->mChild[4]);
        if (tree->mChild[5] != 0xFFFF)
            ShdwDrawRp(shdw, tree->mChild[5]);
        if (tree->mChild[6] != 0xFFFF)
            ShdwDrawRp(shdw, tree->mChild[6]);
        if (tree->mChild[7] != 0xFFFF)
            ShdwDrawRp(shdw, tree->mChild[7]);
    }
}

/* 80249840-80249904       .text ShdwDrawGrpRp__4cBgWFP13cBgS_ShdwDrawi */
void cBgW::ShdwDrawGrpRp(cBgS_ShdwDraw* shdw, int grp_id) {
    if (!pm_grp[grp_id].aab.Cross(shdw->GetBndP()))
        return;

    u32 tree_idx = pm_bgd->m_g_tbl[grp_id].m_tree_idx;
    if (tree_idx != 0xFFFF) {
        ShdwDrawRp(shdw, tree_idx);
    }

    s32 child_idx = pm_bgd->m_g_tbl[grp_id].m_first_child;
    while (true) {
        if (child_idx == 0xFFFF)
            break;
        ShdwDrawGrpRp(shdw, child_idx);
        child_idx = pm_bgd->m_g_tbl[child_idx].m_next_sibling;
    }
}

/* 80249904-8024990C       .text ChkPolyThrough__4cBgWFiP16cBgS_PolyPassChk */
bool cBgW::ChkPolyThrough(int, cBgS_PolyPassChk*) {
    return false;
}

/* 8024990C-80249938       .text ChkShdwDrawThrough__4cBgWFiP16cBgS_PolyPassChk */
bool cBgW::ChkShdwDrawThrough(int param_0, cBgS_PolyPassChk* param_1) {
    return ChkPolyThrough(param_0, param_1);
}

/* 80249938-80249940       .text ChkGrpThrough__4cBgWFiP15cBgS_GrpPassChki */
bool cBgW::ChkGrpThrough(int, cBgS_GrpPassChk*, int) {
    return false;
}

/* 80249940-80249A18       .text GetGrpToRoomIndex__4cBgWCFi */
u32 cBgW::GetGrpToRoomIndex(int grp_index) const {
    JUT_ASSERT(0xc77, 0 <= grp_index && grp_index < pm_bgd->m_g_num);
    cBgD_Grp_t * g_tbl = pm_bgd->m_g_tbl;
    if (g_tbl[grp_index].m_parent == 0xFFFF || g_tbl[g_tbl[grp_index].m_parent].m_parent == 0xFFFF)
        return 0xFFFF;
    return g_tbl[g_tbl[g_tbl[grp_index].m_parent].m_parent].m_room_id;
}

/* 80249A18-80249A58       .text GetTrans__4cBgWCFP4cXyz */
void cBgW::GetTrans(cXyz* dst) const {
    dst->x = (*pm_base)[0][3] - mOldMtx[0][3];
    dst->y = (*pm_base)[1][3] - mOldMtx[1][3];
    dst->z = (*pm_base)[2][3] - mOldMtx[2][3];
}

/* 80249A58-80249B64       .text GetTriPnt__4cBgWCFiP4cXyzP4cXyzP4cXyz */
void cBgW::GetTriPnt(int i_no, cXyz* p0, cXyz* p1, cXyz* p2) const {
    JUT_ASSERT(0xcb3, pm_bgd != NULL);

    cBgD_Tri_t * tri = &pm_bgd->m_t_tbl[i_no];
    p0->set(pm_vtx_tbl[tri->vtx0]);
    p1->set(pm_vtx_tbl[tri->vtx1]);
    p2->set(pm_vtx_tbl[tri->vtx2]);
}

/* 80249B64-80249BA0       .text GetTopUnder__4cBgWCFPfPf */
void cBgW::GetTopUnder(f32* max, f32* min) const {
    *min = pm_grp[m_rootGrpIdx].aab.GetMinP()->y;
    *max = pm_grp[m_rootGrpIdx].aab.GetMaxP()->y;
}
