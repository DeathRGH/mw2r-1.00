#include <stdint.h>
#include <stdarg.h>

#include "debug.h"
#include "defines.h"
#include "detour.h"
#include "functions.h"
#include "global.h"
#include "hooks.h"
#include "host.h"
#include "host_huds.h"
#include "imports.h"
#include "library_functions.h"
#include "menu.h"
#include "menuoptions.h"
#include "types.h"
#include "utility.h"

static int step;
void RgbThread() {
	uartprintf("[MW2R 1.00] RgbThread() -> THREAD STARTED!\n");
	while (ShouldRun()) {
		float inc = 0.005f;//Menu::options.rgbFadingSpeed.current;

		if (step == 0)
			(rgbColor10[2] < (1.0f - inc * 2.0f)) ? rgbColor10[2] += inc : step = 1;
		if (step == 1)
			(rgbColor10[0] > (inc * 2.0f)) ? rgbColor10[0] -= inc : step = 2;
		if (step == 2)
			(rgbColor10[1] < (1.0f - inc * 2.0f)) ? rgbColor10[1] += inc : step = 3;
		if (step == 3)
			(rgbColor10[2] > (inc * 2.0f)) ? rgbColor10[2] -= inc : step = 4;
		if (step == 4)
			(rgbColor10[0] < (1.0f - inc * 2.0f)) ? rgbColor10[0] += inc : step = 5;
		if (step == 5)
			(rgbColor10[1] > (inc * 2.0f)) ? rgbColor10[1] -= inc : step = 0;

		UpdateRGB();
		Sleep(10);
	}

	uartprintf("[MW2R 1.00] RgbThread() -> THREAD ENDED!\n");
}

void LoadMuseum() {
	Cbuf_AddText(LocalClientNum_t::LOCAL_CLIENT_0, "ui_char_museum_mode free");
	Sleep(500);
	Cbuf_AddText(LocalClientNum_t::LOCAL_CLIENT_0, "map ending");
}

void G_GetWeaponForName_DumpingHook(const char *name) {
	uartprintf("[MW2R 1.00] WeaponDump: %s\n", name);
}

void DumpPerks() {
	uint64_t ptr = *(uint64_t *)0x000000000101DC80;
	int index = 1;

	while (ptr > 0) {
		uartprintf("[MW2R 1.00] PerkDump: %s\n", (char *)ptr);
		ptr = *(uint64_t *)(0x000000000101DC80 + (index * 0x08));
		index++;
	}
}

void RunLuaTest() {
	Sleep(100);
	LUIElement *elem = LUI_GetRootElement("UIRootFull", lua_state);

	uartprintf("LUI elem: 0x%llX\n", &elem);
}

void DetectGame() {
	if (!strcmp((char *)0x0000000000D59656, "main_campaign")) {
		executionAddress = 0x0000000000E33FF0;
		NewRunID();
		Sleep(100);

		ScePthread thread1;
		scePthreadCreate(&thread1, NULL, (void *)RgbThread, NULL, "rgb_thread");
		ScePthread thread2;
		scePthreadCreate(&thread2, NULL, (void *)Menu::MonitorButtons, NULL, "monitorButtons_thread");
		ScePthread thread3;
		scePthreadCreate(&thread3, NULL, (void *)Menu::LoopSettings, NULL, "loopSettings_thread");
		///ScePthread thread4;
		///scePthreadCreate(&thread4, NULL, (void *)Host::Forge::MoveForgeEntities, NULL, "forgeMoveEntities_thread");

		char userName[20];
		sceUserServiceGetUserName(userId, userName, 20);

		char welcomeMessage[100];
		snprintf(welcomeMessage, sizeof(welcomeMessage), "Welcome %s!\n[MW2R 1.00] - Loaded\n\nHold  and press .", userName);
		sceSysUtilSendSystemNotificationWithText(222, welcomeMessage);

		Functions::Init();
		Menu::Init();

		//memcpy((void *)0x000000000091FF2A, "\x90\x90\x90\x90\x90", 5); //patch Com_Error for weapon dumping
		//memcpy((void *)0x000000000091FF49, "\x90\x90\x90\x90\x90", 5); //patch Com_Error for weapon dumping
		//memcpy((void *)0x00000000009207B2, "\x90\x90\x90\x90\x90", 5); //patch Com_Error for weapon dumping

		//restore CG_Draw2D
		memcpy((void *)0x0000000000632AE0, "\x55\x48\x89\xE5\x41\x57\x41\x56\x41\x55\x41\x54\x53\x48\x81\xEC\xA8\x09\x00\x00", 20);
		Hooks::CG_Draw2D_Stub = (Hooks::CG_Draw2D_t)DetourFunction(0x0000000000632AE0, (void *)Hooks::CG_Draw2D_Hook, 20);

		// experimental hook for dumping raw/script files
		// all raw files are compressed with zlib 1.1.4
		// fast files are not compressed, only the inner files
		//
		///syscall(136, "/data/dump", 0777); //mkdir
		//restore db_inflate
		///memcpy((void *)0x0000000000E2F090, "\x55\x48\x89\xE5\x41\x57\x41\x56\x41\x55\x41\x54\x53\x50\x48\x89\xFB", 17);
		///Hooks::db_inflate_Stub = (Hooks::db_inflate_t)DetourFunction(0x0000000000E2F090, (void *)Hooks::db_inflate_Hook, 17);

		//restore LUI_Interface_DrawRectangle
		memcpy((void *)0x00000000005C22F0, "\x55\x48\x89\xE5\x41\x57\x41\x56\x41\x55\x41\x54\x53\x48\x81\xEC\xD8\x00\x00\x00", 20);
		Hooks::LUI_Interface_DrawRectangle_Stub = (Hooks::LUI_Interface_DrawRectangle_t)DetourFunction(0x00000000005C22F0, (void *)Hooks::LUI_Interface_DrawRectangle_Hook, 20);

		//restore Scr_NotifyNum
		memcpy((void *)0x00000000009E9B60, "\x55\x48\x89\xE5\x41\x57\x41\x56\x41\x55\x41\x54\x53\x48\x83\xEC\x18", 17);
		Hooks::Scr_NotifyNum_Stub = (Hooks::Scr_NotifyNum_t)DetourFunction(0x00000000009E9B60, (void *)Hooks::Scr_NotifyNum_Hook, 17);

		//restore VM_Notify
		///memcpy((void *)0x0000000000BE5020, "\x55\x48\x89\xE5\x41\x57\x41\x56\x41\x55\x41\x54\x53\x48\x81\xEC\xD8\x04\x00\x00", 20);
		///Hooks::VM_Notify_Stub = (Hooks::VM_Notify_t)DetourFunction(0x0000000000BE5020, (void *)Hooks::VM_Notify_Hook, 20);

		WriteJump(0x0000000000595030, (uint64_t)Hooks::LUI_LuaCall_DebugPrint_Hook);
		//WriteJump(0x00000000008F91F0, (uint64_t)G_GetWeaponForName_DumpingHook);

		//uint64_t assetHeader = DB_FindXAssetHeader(/*XAssetType::ASSET_TYPE_MAP_ENTS*/(XAssetType)0x1C, "maps/mp/mp_pipeline.d3dbsp", 0);
		//uartprintf("[MW2R 1.00] DB_FindXAssetHeader returned: 0x%llX\n", assetHeader);

		//uint64_t assetHeader = DB_FindXAssetHeader(XAssetType::ASSET_TYPE_STRINGTABLE, "mp/botNodePatch.csv", 0);
		//uartprintf("[MW2R 1.00] DB_FindXAssetHeader returned: 0x%llX\n", assetHeader);

		//const char *retVal = SL_ConvertToString((scr_string_t)1278);
		//uartprintf("[MW2R 1.00] SL_ConvertToString returned: %s\n", retVal);

		///PrintLoadedZones();
		///uartprintf("[MW2R 1.00] %s", Host::Entity::GetModelNameFromEntity(0));

		//GScr_MapRestart();

		//scr_string_t cinematic = SL_GetString("hunted_load", 0);
		//char temp[100];
		//snprintf(temp, sizeof(temp), "9 \"%i\" 0", (int)cinematic);
		//SV_GameSendServerCommand(-1, svscmd_type::SV_CMD_RELIABLE, temp);

		//DumpPerks();
		//RunLuaTest();
		//LoadMuseum();
	}
	else {
		sceSysUtilSendSystemNotificationWithText(222, "Welcome to MW2R 1.00");
		OpenMessageDialog("MW2R 1.00\n\nWrong game or update version detected!\n\nSupported:\nCUSA07904 (Update 1.00)");
		return;
	}
}

extern "C" void _main(void) {
	initImports();

	SceUserServiceLoginUserIdList userIdList;
	sceUserServiceGetLoginUserIdList(&userIdList);

	for (int i = 0; i < 4; i++) {
		if (userIdList.userId[i] != -1) {
			userId = userIdList.userId[i];
			break;
		}
	}

	userPadHandle = scePadGetHandle(userId, 0, 0);

	DetectGame();
}

//notes:
//maps d3dbsp at 0x000000000B0FE848 most be something like inside level_locals_t

//0x000000000B0FE8B0 + 0x2C (level_locals_t) set compass objective (0x14 = lines)

//0000000000AD904D   lea r8, dword_1074AB8   inlined G_GetRandomSeed
