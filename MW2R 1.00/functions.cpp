#include "functions.h"

#include "imports.h"

Add_Ammo_t Add_Ammo;

AddBaseDrawTextCmd_t AddBaseDrawTextCmd;

AngleVectors_t AngleVectors;

Cbuf_AddText_t Cbuf_AddText;

CG_CompassDrawActors_t CG_CompassDrawActors;
CG_CompassDrawPlayer_t CG_CompassDrawPlayer;
CG_CompassDrawPlayerMap_t CG_CompassDrawPlayerMap;
CG_DrawRotatedPicPhysical_t CG_DrawRotatedPicPhysical;

CL_ConsolePrint_t CL_ConsolePrint;
CL_DrawTextPhysical_t CL_DrawTextPhysical;

DB_FindXAssetHeader_t DB_FindXAssetHeader;

G_Damage_t G_Damage;
G_DObjGetWorldTagPos_t G_DObjGetWorldTagPos;
G_FindConfigstringIndex_t G_FindConfigstringIndex;
G_FreeEntity_t G_FreeEntity;
G_GetAngles_t G_GetAngles;
G_GetOrigin_t G_GetOrigin;
G_GetPlayerViewOrigin_t G_GetPlayerViewOrigin;
G_GetWeaponForName_t G_GetWeaponForName;
G_LocationalTrace_t G_LocationalTrace;
G_ModelName_t G_ModelName;
G_SetAngle_t G_SetAngle;
G_Spawn_t G_Spawn;

GScr_MapRestart_t GScr_MapRestart;

hks_obj_tolstring_t hks_obj_tolstring;

HudElem_Alloc_t HudElem_Alloc;

LUI_GetRootElement_t LUI_GetRootElement;
LUI_Interface_DrawLine_t LUI_Interface_DrawLine;

PlayerCmd_AllowBoostJump_t PlayerCmd_AllowBoostJump;
PlayerCmd_AllowDodge_t PlayerCmd_AllowDodge;
PlayerCmd_AllowHighJumpDrop_t PlayerCmd_AllowHighJumpDrop;
PlayerCmd_AllowLadder_t PlayerCmd_AllowLadder;
PlayerCmd_AllowMantle_t PlayerCmd_AllowMantle;
PlayerCmd_AllowPowerSlide_t PlayerCmd_AllowPowerSlide;
PlayerCmd_AllowSprint_t PlayerCmd_AllowSprint;
PlayerCmd_ForceMantle_t PlayerCmd_ForceMantle;
PlayerCmd_SetClientDvar_t PlayerCmd_SetClientDvar;
PlayerCmd_setOrigin_t PlayerCmd_setOrigin;

R_AddCmdDrawStretchPic_t R_AddCmdDrawStretchPic;
R_RegisterFont_t R_RegisterFont;
R_TextWidth_t R_TextWidth;

RemoveRefToValue_t RemoveRefToValue;

Scr_AddEntityNum_t Scr_AddEntityNum;
Scr_AddString_t Scr_AddString;
Scr_AddVector_t Scr_AddVector;
Scr_MagicBullet_t Scr_MagicBullet;

ScriptEntCmd_CloneBrushModelToScriptModel_t ScriptEntCmd_CloneBrushModelToScriptModel;
ScriptEntCmd_ScriptModelPlayAnim_t ScriptEntCmd_ScriptModelPlayAnim;
ScriptEntCmd_Solid_t ScriptEntCmd_Solid;

SL_GetStringOfSize_t SL_GetStringOfSize;

SP_script_model_t SP_script_model;

SV_GameSendServerCommand_t SV_GameSendServerCommand;
SV_LinkEntity_t SV_LinkEntity;
SV_SetBrushModel_t SV_SetBrushModel;
SV_UnlinkEntity_t SV_UnlinkEntity;

Sys_Error_t Sys_Error;

Trace_GetEntityHitId_t Trace_GetEntityHitId;











//Custom

void Cmd_RegisterNotification(int clientNum, const char *commandString, const char *notifyString) { //reversed from 0x0000000000A4E227 (GScr_notifyOnPlayerCommand + 0x1F7)
	int numOfNotifications = *(int *)0x0000000002DC9610;
	if (numOfNotifications == 512)
		return;

	int bindKey = Key_GetBindingForCmd(commandString);
	scr_string_t bindString = SL_GetString(notifyString, 0);

	for (int i = 0; i < numOfNotifications; i++) {
		uint64_t commandStart = 0x0000000002DC9620 + (i * 0x0C);
		if (*(int *)commandStart == clientNum && *(int *)(commandStart + 4) == bindKey && *(scr_string_t *)(commandStart + 8) == bindString)
			return;
	}
	
	uint64_t newCommandStart = 0x0000000002DC9620 + (numOfNotifications * 0x0C);
	*(int *)newCommandStart = clientNum;
	*(int *)(newCommandStart + 0x04) = bindKey;
	*(scr_string_t *)(newCommandStart + 0x08) = bindString;
	*(int *)0x0000000002DC9610 = ++numOfNotifications;
}

int G_LocalizedStringIndex(const char *string) { //reversed from 0x0000000000A66DA0 (HECmd_SetText + 0x90)
	int create = *(int *)0x000000000B0FE8B0;
	return G_FindConfigstringIndex(string, (ConfigString)0x21D, 0x28A, create == 0 ? 1 : 0, "localized string");
}

int G_MaterialIndex(const char *name) { //reversed from 0x0000000000AF322A
	return G_FindConfigstringIndex(name, (ConfigString)0xD9A, 0x1A0, 0, "material");
}

int G_ModelIndex(const char *name) { //reversed from 0x0000000000A45DCD (PlayerCmd_SetViewmodel + 0xCD)
	return G_FindConfigstringIndex(name, (ConfigString)0x4D8, 0x400, 0, "model");
	//G_HasCachedModel and G_SetCachedModel still missing, works fine without
}

void G_SetModel(gentity_s *ent, const char *modelName) { //custom
	ent->modelIndex = G_ModelIndex(modelName);
}

void G_SetOrigin(gentity_s *ent, const float *origin) { //custom
	ent->origin[0] = origin[0];
	ent->origin[1] = origin[1];
	ent->origin[2] = origin[2];
}

void HudElem_DestroyAll() { //custom
	int offset = 0;
	while (offset < 0x30000) {
		*(int *)(g_hudelems + offset + 0x1C) = he_type_t::HE_TYPE_FREE;
		offset += 0xD0;
	}
}

void HudElem_DestroyClient(int clientIndex) { //custom
	if (clientIndex == -1) {
		HudElem_DestroyAll();
		return;
	}
	
	int offset = 0;
	while (offset < 0x30000) { //20 at elem + 0x00 && elem + 0x02 //custom check applied in PrecacheElem
		if (*(short *)(g_hudelems + offset + 0x00) == 20 && *(short *)(g_hudelems + offset + 0x02) == 20 && *(int *)(g_hudelems + offset + 0xC0) == clientIndex)
			*(int *)(g_hudelems + offset + 0x1C) = he_type_t::HE_TYPE_FREE;
		offset += 0xD0;
	}
}

int Key_GetBindingForCmd(const char *cmd) { //reversed from 0x0000000000A4E0E6 (GScr_notifyOnPlayerCommand + 0xB6)
	uint64_t *bindCommands = (uint64_t *)g_bindCommands;

	for (int i = 0; i < 45; i++)
		if (!strcmp((const char *)bindCommands[i], cmd))
			return i;

	return 0;
}

void LUI_Interface_DebugPrint(const char *fmt, ...) { //custom
	char buffer[2048];
	va_list args;
	va_start(args, fmt);
	vsprintf(buffer, fmt, args);
	va_end(args);

	char buffer2[2048];
	snprintf(buffer2, sizeof(buffer2), "[MW2R 1.00] <LUI> %s", buffer);
	sceKernelDebugOutText(DGB_CHANNEL_TTYL, buffer2);
}

int R_TextHeight(Font_s *font) { //custom
	return font->pixelHeight;
}

void Scr_AddConstString(scr_string_t value) { //reversed from 0x000000000064BDB6 (Scr_PlayerDamage + 0x126)
	Scr_ClearOutParams();

	uint64_t rax = *(uint64_t *)0x000000000FBC6E28;
	int r15d = *(int *)0x000000000FBC6E34;
	uint64_t rcx = 0x000000000FBD1370;

	if (rax == rcx || rax == *(uint64_t *)0x000000000FBC6E10) {
		Sys_Error("Internal script stack overflow");
		return;
	}

	rcx = rax + 0x10;
	*(uint64_t *)0x000000000FBC6E28 = rcx;
	(*(int *)0x000000000FBC6E30)++;
	*(int *)(rax + 0x18) = 2; //type
	*(int *)(rax + 0x10) = value;

	(*(int *)((value << 4) + *(uint64_t *)0x000000000F0A1D58))++;
}

void Scr_AddEntity(const gentity_s *ent) { //custom
	//Scr_AddEntityNum(ent->number, 0);
}

void Scr_AddInt(int value) { //NOT TESTED
	Scr_ClearOutParams();

	uint64_t rax = *(uint64_t *)0x000000000FBC6E28;
	int r15d = *(int *)0x000000000FBC6E34;
	uint64_t rcx = 0x000000000FBD1370;

	if (rax == rcx || rax == *(uint64_t *)0x000000000FBC6E10) {
		Sys_Error("Internal script stack overflow");
		return;
	}

	rcx = rax + 0x10;
	*(uint64_t *)0x000000000FBC6E28 = rcx;
	(*(int *)0x000000000FBC6E30)++;
	*(int *)(rax + 0x18) = 6; //type
	*(int *)(rax + 0x10) = value;

	(*(int *)((value << 4) + *(uint64_t *)0x000000000F0A1D58))++;
}

void Scr_ClearOutParams() { //reversed from 0x0000000000BE41EA (Scr_AddString + 0x0A)
	int r15d = *(int *)0x000000000FBC6E34;
	if (!r15d)
		return;

	uint64_t rbx = *(uint64_t *)0x000000000FBC6E28;
	uint64_t rax = r15d << 4;
	uint64_t rcx = rbx;
	rbx += 8;
	rcx -= rax;
	*(uint64_t *)0x000000000FBC6E28 = rcx;
	*(int *)0x000000000FBC6E34 = 0;

	while (r15d != 0) {
		RemoveRefToValue(*(int *)rbx, *(VariableUnion *)(rbx - 8));
		rbx -= 0x10;
		r15d--;
	}
}

scr_string_t SL_GetString(const char *str, unsigned int user) { //reversed from 0x0000000000A4E151 (GScr_notifyOnPlayerCommand + 0x121)
	int len = strlen(str) + 1;

	return SL_GetStringOfSize(str, user, len, 0);
}











//UPDATED

Material *Material_RegisterHandle(const char *name, int imageTrack) { //custom
	return (Material *)DB_FindXAssetHeader(XAssetType::ASSET_TYPE_MATERIAL, name, 1);
}

unsigned int Scr_GetSelf(unsigned int threadId) { //reversed from 0x00000000009EA1C6 (VM_Notify + 0x2F6)
	return (unsigned int)(*(unsigned short *)(0x000000000C84C400 + (threadId * 8) + 2));
}

void Scr_SetNumParam(int paramcount) { //reversed from 0x0000000000826A3E (PlayerCmd_EnableMouseSteer + 0x2E)
	*(int *)(0x000000000CD09234) = paramcount;
}

const char *SL_ConvertToString(scr_string_t stringValue) { //reversed from 0x000000000065AB41 (CG_ServerMaterialName + 0x31)
	if (!stringValue)
		return 0;

	return (const char *)(*(uint64_t *)0x000000000C3C4178 + (stringValue << 4) + 8);
}

const char *SL_ConvertToStringSafe(scr_string_t stringValue) { //reversed from 0x000000000065AB41 (CG_ServerMaterialName + 0x31)
	if (!stringValue)
		return "(NULL)";

	return SL_ConvertToString(stringValue);
}

unsigned int SV_GetConfigstringConst(ConfigString index) { //reversed from 0x0000000000826310 (PlayerCmd_GetViewmodel + 0x30)
	return *(unsigned int *)(server_t + (index * 4) + 0x4A50);
}
