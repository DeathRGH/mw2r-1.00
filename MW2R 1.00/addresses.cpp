#include "functions.h"

NAMESPACE(Functions)

void Init() {
	Add_Ammo = (Add_Ammo_t)0x0000000000842550;

	AddBaseDrawTextCmd = (AddBaseDrawTextCmd_t)0x0000000000BC8C30;

	//AngleVectors = (AngleVectors_t)0x0000000000CBCFB0;

	Cbuf_AddText = (Cbuf_AddText_t)0x00000000009ACAA0;

	CG_CompassDrawActors = (CG_CompassDrawActors_t)0x0000000000630800;
	CG_CompassDrawPlayer = (CG_CompassDrawPlayer_t)0x000000000062E7B0;
	CG_CompassDrawPlayerMap = (CG_CompassDrawPlayerMap_t)0x000000000062DEB0;
	CG_DrawRotatedPicPhysical = (CG_DrawRotatedPicPhysical_t)0x0000000000639DE0;

	CL_ConsolePrint = (CL_ConsolePrint_t)0x00000000006CDD10;
	CL_DrawTextPhysical = (CL_DrawTextPhysical_t)0x00000000006DEFF0;
	
	DB_FindXAssetHeader = (DB_FindXAssetHeader_t)0x0000000000736480;
	
	//G_Damage = (G_Damage_t)0x0000000000A5ECE0;
	//G_DObjGetWorldTagPos = (G_DObjGetWorldTagPos_t)0x000000000076B250;
	//G_FindConfigstringIndex = (G_FindConfigstringIndex_t)0x00000000004F8650;
	//G_FreeEntity = (G_FreeEntity_t)0x0000000000AFBBE0;
	//G_GetAngles = (G_GetAngles_t)0x000000000076C310;
	//G_GetPlayerViewOrigin = (G_GetPlayerViewOrigin_t)0x0000000000708BB0;
	//G_GetWeaponForName = (G_GetWeaponForName_t)0x0000000000B05600;
	//G_LocationalTrace = (G_LocationalTrace_t)0x0000000000726550;
	//G_ModelName = (G_ModelName_t)0x000000000043C510;
	//G_SetAngle = (G_SetAngle_t)0x000000000076C230;
	//G_GetOrigin = (G_GetOrigin_t)0x000000000076C2D0;
	//G_Spawn = (G_Spawn_t)0x0000000000AFBAB0;
	
	//GScr_MapRestart = (GScr_MapRestart_t)0x0000000000757FA0;

	hks_obj_tolstring = (hks_obj_tolstring_t)0x0000000000539510;
	
	//HudElem_Alloc = (HudElem_Alloc_t)0x0000000000A64F60;
	
	LUI_GetRootElement = (LUI_GetRootElement_t)0x000000000058DCC0;
	//LUI_Interface_DrawLine = (LUI_Interface_DrawLine_t)0x00000000004F2CA0;
			
	//PlayerCmd_AllowBoostJump = (PlayerCmd_AllowBoostJump_t)0x000000000070F100;
	//PlayerCmd_AllowDodge = (PlayerCmd_AllowDodge_t)0x000000000070F180;
	//PlayerCmd_AllowHighJumpDrop = (PlayerCmd_AllowHighJumpDrop_t)0x000000000070F280;
	//PlayerCmd_AllowLadder = (PlayerCmd_AllowLadder_t)0x000000000070F300;
	//PlayerCmd_AllowMantle = (PlayerCmd_AllowMantle_t)0x000000000070F3B0;
	//PlayerCmd_AllowPowerSlide = (PlayerCmd_AllowPowerSlide_t)0x000000000070F200;
	//PlayerCmd_AllowSprint = (PlayerCmd_AllowSprint_t)0x000000000070F460;
	//PlayerCmd_ForceMantle = (PlayerCmd_ForceMantle_t)0x0000000000710740;
	//PlayerCmd_SetClientDvar = (PlayerCmd_SetClientDvar_t)0x000000000070EA60;
	//PlayerCmd_setOrigin = (PlayerCmd_setOrigin_t)0x000000000070C800;
	
	R_AddCmdDrawStretchPic = (R_AddCmdDrawStretchPic_t)0x00000000006C8AD0;
	R_RegisterFont = (R_RegisterFont_t)0x0000000000BA6160;
	R_TextWidth = (R_TextWidth_t)0x0000000000BA6280;

	//RemoveRefToValue = (RemoveRefToValue_t)0x0000000000BDFEF0;
	
	Scr_AddEntityNum = (Scr_AddEntityNum_t)0x00000000008E4340;
	Scr_AddString = (Scr_AddString_t)0x00000000009FC300;
	Scr_AddVector = (Scr_AddVector_t)0x00000000009FC8F0;
	Scr_MagicBullet = (Scr_MagicBullet_t)0x0000000000887940;

	//ScriptEntCmd_CloneBrushModelToScriptModel = (ScriptEntCmd_CloneBrushModelToScriptModel_t)0x0000000000AEFE40;
	//ScriptEntCmd_ScriptModelPlayAnim = (ScriptEntCmd_ScriptModelPlayAnim_t)0x0000000000AF0090;
	//ScriptEntCmd_Solid = (ScriptEntCmd_Solid_t)0x0000000000AF06C0;
	
	SL_GetStringOfSize = (SL_GetStringOfSize_t)0x00000000009DFFE0;
	
	//SP_script_model = (SP_script_model_t)0x0000000000AEBE50;
	
	SV_GameSendServerCommand = (SV_GameSendServerCommand_t)0x0000000000AE3FE0;
	SV_LinkEntity = (SV_LinkEntity_t)0x0000000000AE90C0;
	//SV_SetBrushModel = (SV_SetBrushModel_t)0x000000000089CFB0;
	//SV_UnlinkEntity = (SV_UnlinkEntity_t)0x00000000008B7460;

	Sys_Error = (Sys_Error_t)0x000000000051B820;
	
	//Trace_GetEntityHitId = (Trace_GetEntityHitId_t)0x00000000007ED970;
}

END
