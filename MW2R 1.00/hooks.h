#pragma once

#include "global.h"
#include "structs.h"

NAMESPACE(Hooks)

typedef void(*CG_Draw2D_t)(LocalClientNum_t localClientNum, float *rsi, float(*rdx)[3]);
extern CG_Draw2D_t CG_Draw2D_Stub;

typedef void(*db_inflate_t)(void *rdi, int esi);
extern db_inflate_t db_inflate_Stub;

typedef void(*LUI_Interface_DrawRectangle_t)(LUIElement *rdi, float xmm0, float xmm1, float xmm2, float xmm3, float xmm4, float xmm5, float xmm6, float xmm7, float xmm8, float xmm9, float xmm10, Material *material, float *rdx, LUI_QuadRenderMode rcx, bool r8, lua_State *r9);
extern LUI_Interface_DrawRectangle_t LUI_Interface_DrawRectangle_Stub;

typedef void(*Scr_NotifyNum_t)(unsigned int notifyListOwnerId, scr_string_t stringValue, unsigned int paramcount);
extern Scr_NotifyNum_t Scr_NotifyNum_Stub;

typedef void(*VM_Notify_t)(unsigned int notifyListOwnerId, scr_string_t stringValue, VariableValue *top);
extern VM_Notify_t VM_Notify_Stub;

//

void CG_Draw2D_Hook(LocalClientNum_t localClientNum, float *rsi, float(*rdx)[3]);

void db_inflate_Hook(void *rdi, int esi);

void LUI_Interface_DrawRectangle_Hook(LUIElement *rdi, float xmm0, float xmm1, float xmm2, float xmm3, float xmm4, float xmm5, float xmm6, float xmm7, float xmm8, float xmm9, float xmm10, Material *material, float *rdx, LUI_QuadRenderMode rcx, bool r8, lua_State *r9);
void LUI_LuaCall_DebugPrint_Hook(lua_State *);

void Scr_NotifyNum_Hook(unsigned int notifyListOwnerId, scr_string_t stringValue, unsigned int paramcount);

void VM_Notify_Hook(unsigned int notifyListOwnerId, scr_string_t stringValue, VariableValue *top);

END
