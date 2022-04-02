#pragma once

#include "global.h"
#include "structs.h"

#define MAX_CLIENTS 1
#define MAX_ENTITYS 2048
#define NUM_FONTS 3
#define NUM_BONES 20

#define ScrPlace (ScreenPlacement *)0x0000000001F8A4D0
#define bg_weaponCompleteDefs 0x000000000E831F00
#define lua_state (lua_State *)(*(uint64_t *)0x00000000018EF9E0)
#define UI_Context (UiContext *)0x0000000002DDC160 //
#define scr_const 0x00000000066B4500 //
#define server_t 0x000000000E8C4C00

#define gentity_t 0x0000000006201880
#define gentity_size 0x2F8
#define gclient_t 0x00000000064F0500
#define gclient_size 0xED00

#define leveltime *(int *)(0x000000000B0FE8B0 + 0x524) //level_locals_t + 0x524 //

#define g_bindCommands 0x000000000104EAA0 //
#define g_hudelems 0x000000000B0BC840 //

//dvars
#define dvar_s_current 0x10
#define dvar_s_default 0x30
#define dvar_s_min 0x40
#define dvar_s_max 0x44
//dvar types (dvar_s + 0x0C) (1 byte)
//0 = bool
//1 = float
//1 = int
//6 = string

#define cg_fov 0x0000000000F2FF08 //

#define cl_ingame 0x00000000027AB638 //

#define MATERIAL_WHITE (Material *)(*(uint64_t *)0x0000000001DEB8B0)

const char *FontForIndex(int index);
const char *FontDisplayNameForIndex(int index);
const char *AimbotBoneForIndex(int index);
const char *MagicBulletProjectileForIndex(int index);
const char *AimbotWeaponForIndex(int index);

int MeansOfDeathForIndex(int index);
const char *MeansOfDeathDisplayNameForIndex(int index);

const char *GetRawWeaponNameForIndex(int id);
const char *GetWeaponNameForIndex(int id);

uint64_t GetTTFForFont(uint64_t font);

bool WorldToScreen(float *worldLocation, float *screen);

void OffHost_EndGame();
void SendConsoleCommand();

extern bool gameEnded;
void PreventCrash();
bool InGame();
bool IsHost();
const char *GetRawGametype();
const char *GetRawMapname();

void DrawText(const char *text, float x, float y, float fontSize, float *color, struct Font_s *font);
void DrawText(const char *text, float x, float y, float fontSize, float *color, const char *font);
void DrawText(const char *text, float x, float y, float fontSize, float *color);
void DrawShader(float x, float y, float width, float height, float *color, struct Material *material);
void DrawShader(float x, float y, float width, float height, float *color, const char *material);
void DrawShader(float x, float y, float width, float height, float *color);
void DrawCenterTextWithBackground(const char *text, float x, float y, float fontSize, float *color, float *backgroundColor, Font_s *font);
void DrawCenterTextWithBackground(const char *text, float x, float y, float fontSize, float *color, float *backgroundColor, const char *font);
void DrawCenterTextWithBackground(const char *text, float x, float y, float fontSize, float *color, float *backgroundColor);
void DrawCenterTextWithBackgroundWithBorder(const char *text, float x, float y, float *color = white10, float fontSize = 0.5f, float *backgroundColor = black08, int borderSize = 2, float *borderColor = white10);
void DrawLine(float x1, float y1, float x2, float y2, float width, float *color);
