#ifndef F_PC_LAYER_ITER_H_
#define F_PC_LAYER_ITER_H_

#include "dolphin/types.h"

typedef struct layer_class layer_class;

typedef int (*fpcLyIt_OnlyHereFunc)(void*, void*);
typedef void* (*fpcLyIt_JudgeFunc)(void*, void*);

BOOL fpcLyIt_OnlyHere(layer_class* pLayer, fpcLyIt_OnlyHereFunc pFunc, void* pUserData);
BOOL fpcLyIt_OnlyHereLY(layer_class* pLayer, fpcLyIt_OnlyHereFunc pFunc, void* pUserData);
void* fpcLyIt_Judge(layer_class* pLayer, fpcLyIt_JudgeFunc pFunc, void* pUserData);
void* fpcLyIt_AllJudge(fpcLyIt_JudgeFunc pFunc, void* pUserData);

#endif
