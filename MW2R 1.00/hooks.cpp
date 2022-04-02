#include "hooks.h"

#include "cache.h"
#include "defines.h"
#include "functions.h"
#include "global.h"
#include "host.h"
#include "imports.h"
#include "menu.h"
#include "menuoptions.h"
#include "structs.h"
#include "utility.h"

NAMESPACE(Hooks)

CG_Draw2D_t CG_Draw2D_Stub;

db_inflate_t db_inflate_Stub;

LUI_Interface_DrawRectangle_t LUI_Interface_DrawRectangle_Stub;

Scr_NotifyNum_t Scr_NotifyNum_Stub;

VM_Notify_t VM_Notify_Stub;

void CG_Draw2D_Hook(LocalClientNum_t localClientNum, float *rsi, float(*rdx)[3]) {
	CG_Draw2D_Stub(localClientNum, rsi, rdx);

	rectDef_s rect;
	rect.x = 0.0f;
	rect.y = 0.0f;
	rect.w = 0.0f;
	rect.h = 0.0f;
	rect.horzAlign = 5;
	rect.vertAlign = 5;

	rectDef_s rect2;
	rect2.x = 100.0f;
	rect2.y = 50.0f;
	rect2.w = 200.0f;
	rect2.h = 200.0f;
	rect2.horzAlign = 0x0C;
	rect2.vertAlign = 0x0D;

	float unknownArray[4][4];
	unknownArray[0][0] = 100.0f;
	unknownArray[0][1] = 50.0f;
	unknownArray[0][2] = 1.0f;
	unknownArray[0][3] = 1.0f;

	unknownArray[1][0] = 300.0f;
	unknownArray[1][1] = 50.0f;
	unknownArray[1][2] = 1.0f;
	unknownArray[1][3] = 1.0f;

	unknownArray[2][0] = 300.0f;
	unknownArray[2][1] = 250.0f;
	unknownArray[2][2] = 1.0f;
	unknownArray[2][3] = 1.0f;

	unknownArray[3][0] = 100.0f;
	unknownArray[3][1] = 250.0f;
	unknownArray[3][2] = 1.0f;
	unknownArray[3][3] = 1.0f;

	//CG_CompassDrawPlayerMap(LocalClientNum_t::LOCAL_CLIENT_0, CompassType::COMPASS_TYPE_PARTIAL, &rect, &rect2, white08, unknownArray);
	//CG_CompassDrawActors(LocalClientNum_t::LOCAL_CLIENT_0, CompassType::COMPASS_TYPE_PARTIAL, &rect, &rect2, white10);
	//CG_CompassDrawPlayer(LocalClientNum_t::LOCAL_CLIENT_0, CompassType::COMPASS_TYPE_PARTIAL, &rect, &rect2, white10, unknownArray);

	Menu::DrawMenu();

	//DrawShader(500.0f, 500.0f, 250.0f, 100.0f, black08);
	//DrawText("Test Text MW2R - DeathRGH", 500.0f, 500.0f, 1.0f, white10);
}

bool shouldWriteFile = false;
void db_inflate_Hook(void *rdi, int esi) { //NOT UPDATED
	int fileHandle;
	register uint64_t r15 asm("r15");
	if (r15) {
		//uartprintf("\ndb_inflate_Hook r15: 0x%llX\n", r15);
		//uartprintf("db_inflate_Hook: %s\n", (char *)(*(uint64_t *)r15));
		//uartprintf("db_inflate_Hook: packed: 0x%llX, final: 0x%llX\n", *(int *)(r15 + 0x08), *(int *)(r15 + 0x0C));

		uint64_t strPtr = *(uint64_t *)r15;

		if (strPtr) {
			char fullFileName[1000];
			strcpy(fullFileName, (char *)(*(uint64_t *)r15));
			uartprintf("[MW2R 1.00] db_inflate: %s\n", fullFileName);

			char folderBuffer[1000];
			strcpy(folderBuffer, "/data/dump");

			char *pch = strtok((char *)fullFileName, "/");

			while (pch != NULL) {
				snprintf(folderBuffer, sizeof(folderBuffer), "%s/%s", folderBuffer, pch);
				if (strstr(pch, (char *)".")) {
					int mode = O_CREAT | O_RDWR | O_TRUNC;
					fileHandle = syscall(5, folderBuffer, mode, 0777); //open
					shouldWriteFile = true;
					break;
				}
				else {
					pch = strtok(NULL, "/");
					syscall(136, folderBuffer, 0777); //mkdir
				}
			}
		}
	}

	db_inflate_Stub(rdi, esi);

	if (r15) {
		register uint64_t r14 asm("r14");
		if (r14 && shouldWriteFile) {
			syscall(4, fileHandle, r14, *(int *)(r15 + 0x0C)); //write
		}
	}
	shouldWriteFile = false;
}

void LUI_Interface_DrawRectangle_Hook(LUIElement *rdi, float xmm0, float xmm1, float xmm2, float xmm3, float xmm4, float xmm5, float xmm6, float xmm7, float xmm8, float xmm9, float xmm10, Material *material, float *rdx, LUI_QuadRenderMode rcx, bool r8, lua_State *r9) {
	if (!strcmp(material->name, "h2_btn_unfocused")) {
		material = Material_RegisterHandle("h1_ui_endgame_scorebar_team", 0);
	}
	else if (!strcmp(material->name, "h2_btn_focused_stroke")) {
		material = Material_RegisterHandle("h1_ui_scoreboard_colorbar_team", 0);
	}
	else if (!strcmp(material->name, "h2_btn_focused_outerglow") || !strcmp(material->name, "h2_btn_focused_fill")) {
		return;
	}
	else if (!strcmp(material->name, "h2_btn_unfocused_locked")) {
		material = Material_RegisterHandle("h1_ui_endgame_scorebar_enemy", 0);
	}
	else if (!strcmp(material->name, "h2_btn_focused_locked")) {
		material = Material_RegisterHandle("h1_ui_scoreboard_colorbar_enemy", 0);
	}
	else if (!strcmp(material->name, "h2_title_splatter_01") || !strcmp(material->name, "h2_title_splatter_02") || !strcmp(material->name, "h2_title_smoke_01") || !strcmp(material->name, "h2_title_smoke_02")) {
		material = Material_RegisterHandle("h1_deco_option_controller_x1", 0);
	}

	LUI_Interface_DrawRectangle_Stub(rdi, xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7, xmm8, xmm9, xmm10, material, rdx, rcx, r8, r9);

	if (Menu::Options.debug_drawMatNames.state)
		DrawText(material->name, xmm0, xmm1, 0.5f, cyan10);
}

void LUI_LuaCall_DebugPrint_Hook(lua_State *rdi) {
	HksObject *rsi = (HksObject *)(*(uint64_t *)((uint64_t)rdi + 0x50));
	unsigned long *rdx = (unsigned long *)((uint64_t)rdi + 0x48);

	if ((uint64_t)rsi < *(uint64_t *)((uint64_t)rdi + 0x48))
		rdx = 0;

	const char *ret = hks_obj_tolstring(rdi, rsi, rdx);
	LUI_Interface_DebugPrint("%s\n", ret);
}

void Scr_NotifyNum_Hook(unsigned int notifyListOwnerId, scr_string_t stringValue, unsigned int paramcount) { //NOT UPDATED
	if (!IsHost()) {
		Scr_NotifyNum_Stub(notifyListOwnerId, stringValue, paramcount);
		return;
	}

	const char *notifyString = SL_ConvertToString(stringValue);
	int entityNum = Scr_GetSelf(notifyListOwnerId);

	if (!strcmp(notifyString, "weapon_fired") && entityNum < MAX_CLIENTS) {
		SV_GameSendServerCommand(0, "gm weapon_fired");
		//uartprintf("%i weapon_fired\n", entityNum);
		//if (Host::Menu::Menu[entnum].magicBullet)
		///Host::FireMagicBullet(entityNum, "at4");//rpg_straight

		//float newPos[3] = { 0.0f, 0.0f, 0.0f };
		//Scr_AddVector(newPos);
		//Scr_SetNumParam(1);
		//PlayerCmd_setOrigin(**(short *)ent);

		//Scr_AddInt(1);
		//Scr_AddString("cg_fov");
		//Scr_AddString("120");
		//Scr_SetNumParam(3);
		//PlayerCmd_SetClientDvar(*(short *)ent);

		//Scr_AddInt(0);
		//Scr_SetNumParam(1);
		//PlayerCmd_ForceMantle(*(short *)ent);

		//float playerPos[3];
		//playerPos[0] = Host::Entity::GetEntityPtr(entnum)->origin[0];
		//playerPos[1] = Host::Entity::GetEntityPtr(entnum)->origin[1];
		//playerPos[2] = Host::Entity::GetEntityPtr(entnum)->origin[2];
		//gentity_s *scriptModel = Host::Entity::SpawnScriptModel("rat", playerPos);//com_plasticcase_beige_big

		//not working yet
		//Scr_AddConstString(0);
		//Scr_AddInt(20);
		//Scr_AddString("animated_rat"); //h1_mp_rat_frantic_idle //frantic //animated_rat_frantic //animated_rat
		//Scr_SetNumParam(2);
		//ScriptEntCmd_ScriptModelPlayAnim(scriptModel->number);

		//gentity_s *collision = Host::Entity::FindCollision("pipe_shootable");//pf1958_auto1
		//
		//if (collision) {
		//	Scr_AddEntity(collision);
		//	Scr_SetNumParam(1);
		//	ScriptEntCmd_CloneBrushModelToScriptModel(scriptModel->number);
		//	ScriptEntCmd_Solid(scriptModel->number);
		//}

		//if (Host::Menu::Menu[entnum].unfairAimbot) {
		//	float playerAngles[3];
		//	playerAngles[0] = Host::Entity::GetEntityPtr(entnum)->client->angles[0];
		//	playerAngles[1] = Host::Entity::GetEntityPtr(entnum)->client->angles[1];
		//	playerAngles[2] = Host::Entity::GetEntityPtr(entnum)->client->angles[2];
		//
		//	float forward[3];
		//	AngleVectors(playerAngles, forward, 0, 0);
		//	G_Damage(Host::Entity::GetEntityPtr(Host::ClosestClient(entnum)), Host::Entity::GetEntityPtr(entnum), Host::Entity::GetEntityPtr(entnum), forward, playerAngles, 100000, 0, (meansOfDeath_t)MeansOfDeathForIndex(Host::Menu::Menu[entnum].aimbotMod), Host::Entity::GetEntityPtr(entnum)->client->weapon, false, 0, hitLocation_t::HITLOC_TORSO_UPR, 0, 84, 0);
		//}

		if (Menu::Options.debug_infAmmo.state) {
			Add_Ammo((playerState_s *)Host::Entity::GetEntityPtr(entityNum)->client, Host::Entity::GetEntityPtr(entityNum)->client->weapon, false, 999, 1);
			Add_Ammo((playerState_s *)Host::Entity::GetEntityPtr(entityNum)->client, Host::Entity::GetEntityPtr(entityNum)->client->weapon, true, 999, 1);
		}
	}

	if (!strcmp(SL_ConvertToString(stringValue), "grenade_fire") && entityNum < MAX_CLIENTS) {
		if (Menu::Options.debug_infAmmo.state) {
			Add_Ammo((playerState_s *)Host::Entity::GetEntityPtr(entityNum)->client, Host::Entity::GetEntityPtr(entityNum)->client->lethalWeapon, false, 999, 1);
			Add_Ammo((playerState_s *)Host::Entity::GetEntityPtr(entityNum)->client, Host::Entity::GetEntityPtr(entityNum)->client->tacticalWeapon, false, 999, 1);
		}
	}

	Scr_NotifyNum_Stub(notifyListOwnerId, stringValue, paramcount);
}

void VM_Notify_Hook(unsigned int notifyListOwnerId, scr_string_t stringValue, VariableValue *top) { //NOT UPDATED
	if (!IsHost()) {
		VM_Notify_Stub(notifyListOwnerId, stringValue, top);
		return;
	}

	const char *notifyString = SL_ConvertToString(stringValue);
	int entityNum = Scr_GetSelf(notifyListOwnerId);

	if (!strcmp(notifyString, "player_spawned")) {
		int spawnedClientIndex = Scr_GetSelf(top->u.entityOffset);

		char temp[100];
		snprintf(temp, sizeof(temp), "f \"^2spawnedClientIndex: %i\"", spawnedClientIndex);
		SV_GameSendServerCommand(-1, temp);

		SV_GameSendServerCommand(spawnedClientIndex, "f \"Press \x0017 ^7to ^2open ^7the menu.\"");

		Cmd_RegisterNotification(spawnedClientIndex, "+actionslot 1", "DPAD_UP");
		Cmd_RegisterNotification(spawnedClientIndex, "+actionslot 2", "DPAD_DOWN");
		Cmd_RegisterNotification(spawnedClientIndex, "+actionslot 3", "DPAD_LEFT");
		Cmd_RegisterNotification(spawnedClientIndex, "+actionslot 4", "DPAD_RIGHT");
		Cmd_RegisterNotification(spawnedClientIndex, "+gostand", "BTN_X");
		Cmd_RegisterNotification(spawnedClientIndex, "+usereload", "BTN_SQUARE");
		Cmd_RegisterNotification(spawnedClientIndex, "+frag", "BTN_R1");
		//Cmd_RegisterNotification(spawnedClientIndex, "+melee_zoom", "BUTTON_R3");

		Host::Menu::OnPlayerSpawned(spawnedClientIndex);
	}
	if (!strcmp(notifyString, "DPAD_UP")) {
		Host::Menu::ScrollUp(entityNum);

		//float pos[3] = { 0.0f, 0.0f, 1000000.0f };
		//gentity_s *ent = Host::Entity::SpawnScriptModel("com_plasticcase_green_big_us_dirt", pos);
		//gentity_s *collision = Host::Entity::FindCollision("pf1_auto1");//pf13_auto1
		//Host::Entity::CloneBrushModelToScriptModel(ent, collision);
		//Host::Entity::Solid(ent);
		//Host::Forge::clientCurrentEntity[entityNum] = ent;
	}
	if (!strcmp(notifyString, "DPAD_DOWN")) {
		Host::Menu::ScrollDown(entityNum);

		/*if (Host::Forge::clientCurrentEntity[entityNum] != 0)
			Host::Forge::clientCurrentEntity[entityNum] = 0;
		else
			Host::Forge::PickupEntity(Host::Entity::GetEntityPtr(entityNum))*/;
	}
	if (!strcmp(notifyString, "BTN_X")) {
		Host::Menu::Select(entityNum);
	}
	if (!strcmp(notifyString, "BTN_SQUARE")) {
		Host::Menu::GoBack(entityNum);
	}
	if (!strcmp(notifyString, "DPAD_LEFT")) {
		char temp[100];
		snprintf(temp, sizeof(temp), "f \"^3client: %i hit DPAD_LEFT\"", entityNum);
		SV_GameSendServerCommand(-1, temp);
	}
	if (!strcmp(notifyString, "DPAD_RIGHT")) {
		Host::Menu::OpenCloseMenu(entityNum);

		/*if (Host::Forge::clientCurrentEntity[entityNum] != 0)
			G_FreeEntity(Host::Forge::clientCurrentEntity[entityNum]);
		else
			Host::Forge::DeleteEntity(Host::Entity::GetEntityPtr(entityNum));

		Host::Forge::clientCurrentEntity[entityNum] = 0;*/
	}
	if (!strcmp(notifyString, "BTN_R1")) {
		char temp[100];
		snprintf(temp, sizeof(temp), "f \"^3client: %i hit BTN_R1\"", entityNum);
		SV_GameSendServerCommand(-1, temp);

		//*(char *)(gclient_t + 0x5370 + (entityNum * gclient_size)) ^= 1;
		///Host::Entity::ToggleNoclip(entityNum);
		///SV_GameSendServerCommand(-1, svscmd_type::SV_CMD_RELIABLE, Host::Entity::GetEntityPtr(entityNum)->client->mFlag[0] == 2 ? "f \"Noclip [^2ON^7]\"" : "f \"Noclip [^1OFF^7]\"");

		//float playerPos[3];
		//playerPos[0] = Host::Entity::GetEntityPtr(entityNum)->origin[0];
		//playerPos[1] = Host::Entity::GetEntityPtr(entityNum)->origin[1];
		//playerPos[2] = Host::Entity::GetEntityPtr(entityNum)->origin[2];
		//Host::Entity::SpawnScriptModel("com_plasticcase_beige_big", playerPos);
		//should try to use the script cmd for cloning here as it at most pushes 2 ents

		//gentity_s *collision = Host::Entity::FindCollision("pf1958_auto1");
	}
	if (!strcmp(notifyString, "weapon_inspection")) {
		if (Host::Menu::menuOpen[entityNum])
			return;
	}

	VM_Notify_Stub(notifyListOwnerId, stringValue, top);
}

END
