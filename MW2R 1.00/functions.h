#pragma once

#include "global.h"
#include "host_huds.h"
#include "structs.h"
#include "types.h"

typedef void(*Add_Ammo_t)(playerState_s *, Weapon, bool, int count, int fillClip);

typedef GfxCmdDrawText2D *(*AddBaseDrawTextCmd_t)(const char *text, int maxChars, Font_s *font, int fontHeight, float x, float y, float xScale, float yScale, float rotation, const float *color, int style, int cursorPos, char cursor, FontGlowStyle *glowStyle);

typedef void(*AngleVectors_t)(const float *angles, float *forward, float *right, float *up);

typedef void(*Cbuf_AddText_t)(LocalClientNum_t localClientNum, const char *text);

typedef void(*CG_CompassDrawActors_t)(LocalClientNum_t localClientNum, CompassType compassType, const rectDef_s *parentRect, const rectDef_s *rect, float *color);
typedef void(*CG_CompassDrawPlayer_t)(LocalClientNum_t localClientNum, CompassType compassType, const rectDef_s *parentRect, rectDef_s *rect, float *color, float const (*)[4]);
typedef void(*CG_CompassDrawPlayerMap_t)(LocalClientNum_t localClientNum, CompassType compassType, const rectDef_s *parentRect, const rectDef_s *rect, float *color, float const (*)[4]);
typedef void(*CG_DrawRotatedPicPhysical_t)(const ScreenPlacement *screenPlacement, float x, float y, float width, float height, float angle, const float *color, Material *material);

typedef void(*CL_ConsolePrint_t)(int channel, const char *txt, int duration, int pixelWidth, int flags);
typedef void(*CL_DrawTextPhysical_t)(const char *text, int maxChars, Font_s *font, float x, float y, float xScale, float yScale, const float *color, int style);

typedef uint64_t(*DB_FindXAssetHeader_t)(XAssetType type, const char *name, int allowCreateDefault);

typedef void(*G_Damage_t)(gentity_s *targ, const gentity_s *inflictor, gentity_s *attacker, const float *dir, const float *point, int damage, int dFlags, meansOfDeath_t mod, Weapon weapon, bool u1, int u2, hitLocation_t hitLoc, unsigned int modelIndex, scr_string_t partName, int timeOffset);
typedef int(*G_DObjGetWorldTagPos_t)(const gentity_s *ent, scr_string_t tagName, float *pos);
typedef int(*G_FindConfigstringIndex_t)(const char *name, ConfigString start, unsigned int max, int create, const char *errormsg);
typedef void(*G_FreeEntity_t)(gentity_s *ed);
typedef void(*G_GetAngles_t)(LocalClientNum_t localClientNum, short entIndex, float *outAngles);
typedef void(*G_GetOrigin_t)(LocalClientNum_t localClientNum, short entIndex, float *outPosition);
typedef void(*G_GetPlayerViewOrigin_t)(const playerState_s *ps, float *origin);
typedef Weapon(*G_GetWeaponForName_t)(const char* name);
typedef void(*G_LocationalTrace_t)(/*trace_t **/void *results, const float *start, const float *end, short passEntityNum, int contentmask, unsigned char *priorityMap);
typedef unsigned int(*G_ModelName_t)(int index);
typedef void(*G_SetAngle_t)(gentity_s *ent, const float *angle);
typedef gentity_s *(*G_Spawn_t)();

typedef void(*GScr_MapRestart_t)();

typedef const char *(*hks_obj_tolstring_t)(lua_State *, HksObject *, unsigned long *);

typedef game_hudelem_s *(*HudElem_Alloc_t)(int clientNum, int teamNum);

typedef LUIElement *(*LUI_GetRootElement_t)(const char *, lua_State *);
typedef void(*LUI_Interface_DrawLine_t)(LUIElement *, float x1, float y1, float x2, float y2, unsigned char, float, float r, float g, float b, float a);

typedef void(*PlayerCmd_AllowBoostJump_t)(scr_entref_t entref);
typedef void(*PlayerCmd_AllowDodge_t)(scr_entref_t entref);
typedef void(*PlayerCmd_AllowHighJumpDrop_t)(scr_entref_t entref);
typedef void(*PlayerCmd_AllowLadder_t)(scr_entref_t entref);
typedef void(*PlayerCmd_AllowMantle_t)(scr_entref_t entref);
typedef void(*PlayerCmd_AllowPowerSlide_t)(scr_entref_t entref);
typedef void(*PlayerCmd_AllowSprint_t)(scr_entref_t entref);
typedef void(*PlayerCmd_ForceMantle_t)(scr_entref_t entref);
typedef void(*PlayerCmd_SetClientDvar_t)(scr_entref_t entref);
typedef void(*PlayerCmd_setOrigin_t)(scr_entref_t entref);

typedef void(*R_AddCmdDrawStretchPic_t)(float x, float y, float w, float h, float s0, float t0, float s1, float t1, const float *color, Material *material);
typedef Font_s *(*R_RegisterFont_t)(const char *name, int pixelHeight, int imageTrack);
typedef int(*R_TextWidth_t)(const char *text, int maxChars, Font_s *font);

typedef void(*RemoveRefToValue_t)(int type, VariableUnion u);

typedef void(*Scr_AddEntityNum_t)(int entnum, unsigned int classnum);
typedef void(*Scr_AddString_t)(const char *value);
typedef void(*Scr_AddVector_t)(const float *value);
typedef void(*Scr_MagicBullet_t)();

typedef void(*ScriptEntCmd_CloneBrushModelToScriptModel_t)(scr_entref_t entref);
typedef void(*ScriptEntCmd_ScriptModelPlayAnim_t)(scr_entref_t entref);
typedef void(*ScriptEntCmd_Solid_t)(scr_entref_t entref);

typedef scr_string_t(*SL_GetStringOfSize_t)(const char *str, unsigned int user, unsigned int len, int type);

typedef void(*SP_script_model_t)(gentity_s *pSelf);

typedef void(*SV_GameSendServerCommand_t)(signed char clientNum, const char *text);
typedef void(*SV_LinkEntity_t)(gentity_s *gEnt);
typedef void(*SV_SetBrushModel_t)(gentity_s *ent);
typedef void(*SV_UnlinkEntity_t)(gentity_s *gEnt);

typedef void(*Sys_Error_t)(const char *error, ...);

typedef unsigned short(*Trace_GetEntityHitId_t)(/*const trace_t **/void *trace);

//

extern Add_Ammo_t Add_Ammo;

extern AddBaseDrawTextCmd_t AddBaseDrawTextCmd;

extern AngleVectors_t AngleVectors;

extern Cbuf_AddText_t Cbuf_AddText;

extern CG_CompassDrawActors_t CG_CompassDrawActors;
extern CG_CompassDrawPlayer_t CG_CompassDrawPlayer;
extern CG_CompassDrawPlayerMap_t CG_CompassDrawPlayerMap;
extern CG_DrawRotatedPicPhysical_t CG_DrawRotatedPicPhysical;

extern CL_ConsolePrint_t CL_ConsolePrint;
extern CL_DrawTextPhysical_t CL_DrawTextPhysical;

extern DB_FindXAssetHeader_t DB_FindXAssetHeader;

extern G_Damage_t G_Damage;
extern G_DObjGetWorldTagPos_t G_DObjGetWorldTagPos;
extern G_FindConfigstringIndex_t G_FindConfigstringIndex;
extern G_FreeEntity_t G_FreeEntity;
extern G_GetAngles_t G_GetAngles;
extern G_GetOrigin_t G_GetOrigin;
extern G_GetPlayerViewOrigin_t G_GetPlayerViewOrigin;
extern G_GetWeaponForName_t G_GetWeaponForName;
extern G_LocationalTrace_t G_LocationalTrace;
extern G_ModelName_t G_ModelName;
extern G_SetAngle_t G_SetAngle;
extern G_Spawn_t G_Spawn;

extern GScr_MapRestart_t GScr_MapRestart;

extern hks_obj_tolstring_t hks_obj_tolstring;

extern HudElem_Alloc_t HudElem_Alloc;

extern LUI_GetRootElement_t LUI_GetRootElement;
extern LUI_Interface_DrawLine_t LUI_Interface_DrawLine;

extern PlayerCmd_AllowBoostJump_t PlayerCmd_AllowBoostJump;
extern PlayerCmd_AllowDodge_t PlayerCmd_AllowDodge;
extern PlayerCmd_AllowHighJumpDrop_t PlayerCmd_AllowHighJumpDrop;
extern PlayerCmd_AllowLadder_t PlayerCmd_AllowLadder;
extern PlayerCmd_AllowMantle_t PlayerCmd_AllowMantle;
extern PlayerCmd_AllowPowerSlide_t PlayerCmd_AllowPowerSlide;
extern PlayerCmd_AllowSprint_t PlayerCmd_AllowSprint;
extern PlayerCmd_ForceMantle_t PlayerCmd_ForceMantle;
extern PlayerCmd_SetClientDvar_t PlayerCmd_SetClientDvar;
extern PlayerCmd_setOrigin_t PlayerCmd_setOrigin;

extern R_AddCmdDrawStretchPic_t R_AddCmdDrawStretchPic;
extern R_RegisterFont_t R_RegisterFont;
extern R_TextWidth_t R_TextWidth;

extern RemoveRefToValue_t RemoveRefToValue;

extern Scr_AddEntityNum_t Scr_AddEntityNum;
extern Scr_AddString_t Scr_AddString;
extern Scr_AddVector_t Scr_AddVector;
extern Scr_MagicBullet_t Scr_MagicBullet;

extern ScriptEntCmd_CloneBrushModelToScriptModel_t ScriptEntCmd_CloneBrushModelToScriptModel;
extern ScriptEntCmd_ScriptModelPlayAnim_t ScriptEntCmd_ScriptModelPlayAnim;
extern ScriptEntCmd_Solid_t ScriptEntCmd_Solid;

extern SL_GetStringOfSize_t SL_GetStringOfSize;

extern SP_script_model_t SP_script_model;

extern SV_GameSendServerCommand_t SV_GameSendServerCommand;
extern SV_LinkEntity_t SV_LinkEntity;
extern SV_SetBrushModel_t SV_SetBrushModel;
extern SV_UnlinkEntity_t SV_UnlinkEntity;

extern Sys_Error_t Sys_Error;

extern Trace_GetEntityHitId_t Trace_GetEntityHitId;











//Custom

void Cmd_RegisterNotification(int clientNum, const char *commandString, const char *notifyString);

int G_LocalizedStringIndex(const char *string);
int G_MaterialIndex(const char *name);
int G_ModelIndex(const char *name);
void G_SetModel(gentity_s *ent, const char *modelName);
void G_SetOrigin(gentity_s *ent, const float *origin);

void HudElem_DestroyAll();
void HudElem_DestroyClient(int clientIndex);

int Key_GetBindingForCmd(const char *cmd);

void LUI_Interface_DebugPrint(const char *fmt, ...);

int R_TextHeight(Font_s *font);

void Scr_AddConstString(scr_string_t value);
void Scr_AddEntity(const gentity_s *ent);
void Scr_AddInt(int value);
void Scr_ClearOutParams();

scr_string_t SL_GetString(const char *str, unsigned int user);











//UPDATED
Material *Material_RegisterHandle(const char *name, int imageTrack);

unsigned int Scr_GetSelf(unsigned int threadId);
void Scr_SetNumParam(int paramcount);

const char *SL_ConvertToString(scr_string_t stringValue);
const char *SL_ConvertToStringSafe(scr_string_t stringValue);

unsigned int SV_GetConfigstringConst(ConfigString index);

NAMESPACE(Functions)

void Init();

END
