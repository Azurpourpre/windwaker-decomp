#ifndef D_A_SHAND_H
#define D_A_SHAND_H

#include "SSystem/SComponent/c_phase.h"
#include "d/d_cc_d.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"

typedef struct {
    /* 0x00 */ cXyz mPos;
    u8 _pad[0x18 - 0xc];
    /* 0x18 */ float u18;
} shand_s;

class shand_class : public fopAc_ac_c {
public:
    u8 _pad290[0x2AB - 0x290];
    /* 0x2AC */ request_of_phase_process_class mPhs;
    /* 0x2B4 */ short mExecuteCount;
    short _pad2B6;
    /* 0x2B8 */ short mState;
    /* 0x2BA */ short u2BA;
    /* 0x2BC */ short u2BC[4];
    /* 0x2C4 */ short u2C4;
    /* 0x2C8 */ cXyz u2C8;
    /* 0x2D4 */ cXyz u2D4;
    u8 _pad2E0[0x2F0 - 0x2E0];
    /* 0x2F0 */ float u2F0; 
    /* 0x2F4 */ float u2F4; 
    /* 0x2F8 */ float u2F8; 
    /* 0x2FC */ float u2FC;
    /* 0x300 */ float u300;
    /* 0x304 */ float u304;
    /* 0x308 */ fpc_ProcID u308;
    /* 0x30C */ shand_class* u30C;
    /* 0x310 */ cXyz* u310;
    /* 0x314 */ u8* u314;
    /* 0x318 */ short u318;
    /* 0x31C */ shand_s u31C[20]; 
    /* 0x54C */ mDoExt_3DlineMat1_c mLineMat;
    /* 0x588 */ dCcD_Stts mStts;
    /* 0x5C4 */ dCcD_Sph mSph;
    /* 0x6F0 */ dCcD_Cyl mCylArr[5];
    /* 0xCE0 */ float uCE0;
    /* 0xCE4 */ bool mHasHIO;
};

class daShand_HIO_c : public JORReflexible {
public:
    daShand_HIO_c();
    virtual ~daShand_HIO_c(){};

    void genMessage(JORMContext* ctx){};

public:
    /* 0x0    vtable */
    /* 0x4 */ s8 mId;
    /* 0x6 */ short u6;
    /* 0x8 */ short u8;
};

#endif /* D_A_SHAND_H */
