#include "includes.h"
#include "attributes.h"
#include "offsets.h"
#include "types.h"
#include "process.h"
#include "vector.h"
#include "string.h"
#include "matrix.h"
#include "utility.h"
#include "IniWriter.h"
#include "IniReader.h"
#include "XorStr.hpp"
#include "speedhack.h"
#include <iostream>
#include <winuser.h>
#include <vector>
#include <string>


// Credential goes to https://www.codeproject.com/Articles/10809/A-Small-Class-to-Read-INI-File
// IniWriter and IniReader by Xiangxiong Jian
// licensed under The Code Project Open License (CPOL)


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

CIniWriter iniWriter((char*)CONFIG_PATH);
CIniReader iniReader((char*)CONFIG_PATH);

static float res_x, res_y;
static bool G_ESP;
static bool G_Box_npc;
static bool G_Box_player;
static bool G_Skeleton_player;
static bool G_Skeleton_npc;
static bool G_Snapline_player;
static bool G_Snapline_npc;
static bool G_Recoil;
static bool G_Spread;
static bool G_Reload;
static bool G_RPM;
static bool G_Teleport;
static bool G_Health;
static bool G_Speedhack;
static bool show_menu = true;
static int TELEPORT_MAP_KEY;
static int TELEPORT_XHAIR_KEY;
static int SPEEDHACK_KEY;
static int MENU_KEY;
static bool speedhack_key_pressed = false;
static bool teleport_xhair_key_pressed = false;
static bool menu_key_pressed = false;
static ImColor color_npc_friendly;
static ImColor color_npc_hostile;
static ImColor color_player_friendly;
static ImColor color_player_rogue;
static ImColor color_player_blacklisted;

static char TELEPORT_PLAYER_CURRENT_COORDS[1024];

typedef struct {
	vec3 pos;
	int key;
	bool loaded;
} warp;
static warp warps[MAX_TELEPORTS];
static vec3 tmp = { -1, -1, -1 };


static float value_RPM = 66666.f;
static float value_Speedhack;
static bool g_is_init = false;
static bool init = false;
static uintptr_t g_base_ptr;
static int g_indices[AtributeIndexMax];
static std::vector<std::string> blacklist;
static std::vector<std::string> whitelist;


// static vec3 blacklist_color = vec3_set(72, 209, 204);


template<typename T> T read_memory(uintptr_t address)
{
	try { return *(T*)address; }
	catch (...) {
		return T();
	}
}


template<typename T> void write_memory(uintptr_t address, T value)
{
	try { *(T*)address = value; }
	catch (...) { return; }
}

// https://cplusplus.com/forum/beginner/14349/
void toClipboard(const std::string& s) {
	OpenClipboard(0);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size());
	if (!hg) {
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), s.c_str(), s.size());
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}


void DoStyle()
{
	ImGuiStyle* style = &ImGui::GetStyle();
	style->WindowTitleAlign = ImVec2(0.5, 0.5);
	style->WindowMinSize = ImVec2(600, 240);
	style->WindowPadding = ImVec2(15, 15);
	style->WindowRounding = 5.0f;
	style->FramePadding = ImVec2(8, 6);
	style->FrameRounding = 4.0f;
	style->ItemSpacing = ImVec2(12, 8);
	style->ItemInnerSpacing = ImVec2(8, 6);
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 15.0f;
	style->ScrollbarRounding = 9.0f;
	style->GrabMinSize = 5.0f;
	style->GrabRounding = 3.0f;

	style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_ChildBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	// style->Colors[ImGuiCol_ComboBg] = ImVec4(0.19f, 0.18f, 0.21f, 1.00f);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	// style->Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	// style->Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	// style->Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	// style->Colors[ImGuiCol_CloseButton] = ImVec4(0.40f, 0.39f, 0.38f, 0.16f);
	// style->Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
	// style->Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
	style->Alpha = 0.8f;
}

void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

typedef struct entity {
	uintptr_t ptr;
	bool is_gadget, is_human, is_rogue, is_player, is_friendly;
	int level, hp_cur, hp_max;

	vec3 pos, torso, belly, head, neck;
	vec3 left_foot, left_thigh, left_knee, left_shoulder, left_elbow, left_hand;
	vec3 right_foot, right_thigh, right_knee, right_shoulder, right_elbow, right_hand;
	char name[16] = { '?', '\0' };
} entity;
static entity entitylist[MAX_ENTITIES];


char* str_settings = (char*)"Settings";
char* str_keys = (char*)"Keys";
char* str_teleports = (char*)"Teleports";
char* str_speedhack = (char*)"Speedhack";
char* str_teleport_xhair = (char*)"TeleportXhair";
char* str_teleport_map = (char*)"TeleportMap";
char* str_menu = (char*)"Menu";
char* str_lists = (char*)"Lists";
char* str_blacklist = (char*)"BlackList";
char* str_whitelist = (char*)"WhiteList";
char* str_colors = (char*)"Colors";
char* str_npc_friendly = (char*)"NPCFriendly";
char* str_npc_hostile = (char*)"NPCHostile";
char* str_player_friendly = (char*)"PlayerFriendly";
char* str_player_rogue = (char*)"PlayerRogue";
char* str_player_blacklisted = (char*)"PlayerBlacklisted";
char* str_ratio = (char*)"Ratio";


const char* CONF_TELEPORT_DST_NAMES[MAX_TELEPORTS] = {
	"Pos0",
	"Pos1",
	"Pos2",
	"Pos3",
	"Pos4",
	"Pos5",
	"Pos6",
	"Pos7",
	"Pos8",
	"Pos9",
	"Pos10",
	"Pos11",
	"Pos12",
	"Pos13",
	"Pos14",
	"Pos15"
};

static char* get_vk_name(int x) {

	for (int i = 0; i < ARRAYSIZE(CONFIG_KEYS); i++) {
		if (x == CONFIG_KEYS[i].vk) return (char*)CONFIG_KEYS[i].key;
	}

	return (char*)"?";
}

// Reads a bone position from the game.
static vec3 get_bone_pos(uintptr_t bone_ptr, UINT index) {
	return read_memory<vec3>(bone_ptr + index * 0x40 + 0x30);
}

// Reads a value index from the game.
// static float get_index(uintptr_t ii_arr, UINT val) {
// 	u64 base = process_read_u64(ii_arr + val * 8);
// 	return process_read_float(base + 0x50);
// }

// Reads an index value.
// static float get_index_val(uintptr_t ii_arr, UINT index) {
//	return process_read_float(ii_arr + g_indices[index] * 64 + 0x4);
//}

// Sets an index value.
static void set_index_val(uintptr_t ii_arr, int index, float val) {
	try {
		write_memory<float>(ii_arr + g_indices[index] * 0x40 + 0x4, val);
	}
	catch (...) {}
}

bool iequals(const std::string& a, const std::string& b)
{
	unsigned int sz = a.size();
	if (b.size() != sz)
		return false;
	for (unsigned int i = 0; i < sz; ++i)
		if (tolower(a[i]) != tolower(b[i]))
			return false;
	return true;
}

bool is_blacklisted(char* name) {

	std::string sname = std::string(name);
	for (int i = 0; i < blacklist.size(); i++) {
		if (iequals(sname, blacklist[i])) return true;
	}
	return false;
}

bool is_whitelisted(char* name) {

	std::string sname = std::string(name);
	for (int i = 0; i < whitelist.size(); i++) {
		if (iequals(sname, blacklist[i])) return true;
	}
	return false;
}

// Transforms a 3D coordinate into the 2D screen space.
ImVec2 w2s(vec3 pos, mat4 world, float hx, float hy) {
	vec3 tv = vec3_set(world._41, world._42, world._43);
	vec3 up = vec3_set(world._21, world._22, world._23);
	vec3 ri = vec3_set(world._11, world._12, world._13);

	float w = vec3_dot(tv, pos) + world._44;

	if (w < -1.f) {
		return ImVec2(0, 0);
	}

	float x = (vec3_dot(ri, pos) + world._14);
	float y = (vec3_dot(up, pos) + world._24);

	return ImVec2(hx * (1.0f + x / w) + x / w, hy * (1.0f - y / w) + y / w);
}


// https://blog.csdn.net/m0_58086930/article/details/122759927
void stringsplit(const char* str, const std::string& split, std::vector<std::string>& res)
{
	char* strc = new char[strlen(str) + 1];
	strcpy_s(strc, strlen(str) + 1, str);  // copy str to strc (str in char form)
	char* ptr = NULL;
	char* temp = strtok_s(strc, split.c_str(), &ptr);
	while (temp != NULL)
	{
		if (strlen(temp) > 0) res.push_back(std::string(temp));
		temp = strtok_s(NULL, split.c_str(), &ptr);	// next string to split
	}
	delete[] strc;
}


static bool game_init(void) {

	// Open the process.
	g_base_ptr = (uintptr_t)GetModuleHandle(0);
	// Get the base pointer for the module.

	if (g_base_ptr == 0) {
		return false;
	}
	
	try {
		G_ESP = iniReader.ReadBoolean(str_settings, (char*)"ESP", true);
		G_Box_npc = iniReader.ReadBoolean(str_settings, (char*)"Box_npc", true);
		G_Box_player = iniReader.ReadBoolean(str_settings, (char*)"Box_player", true);
		G_Skeleton_npc = iniReader.ReadBoolean(str_settings, (char*)"Skeleton_npc", false);
		G_Skeleton_player = iniReader.ReadBoolean(str_settings, (char*)"Skeleton_player", false);
		G_Snapline_npc = iniReader.ReadBoolean(str_settings, (char*)"Snapline_npc", true);
		G_Snapline_player = iniReader.ReadBoolean(str_settings, (char*)"Snapline_player", true);
		G_Recoil = iniReader.ReadBoolean(str_settings, (char*)"Recoil", true);
		G_Spread = iniReader.ReadBoolean(str_settings, (char*)"Spread", true);
		G_Reload = iniReader.ReadBoolean(str_settings, (char*)"Reload", true);
		G_RPM = iniReader.ReadBoolean(str_settings, (char*)"RPM", true);
		G_Teleport = iniReader.ReadBoolean(str_settings, (char*)"Teleport", true);
		G_Health = iniReader.ReadBoolean(str_settings, (char*)"Health", true);
		G_Speedhack = iniReader.ReadBoolean(str_settings, str_speedhack, false);
	}
	catch (...) {
		G_ESP = true;
		G_Box_npc = false;
		G_Box_player = false;
		G_Skeleton_player = true;
		G_Skeleton_npc = false;
		G_Snapline_player = true;
		G_Snapline_npc = false;
		G_Recoil = true;
		G_Spread = true;
		G_Reload = true;
		G_RPM = true;
		G_Teleport = true;
		G_Health = true;
		G_Speedhack = false;
	}

	try {
		TELEPORT_XHAIR_KEY = iniReader.ReadInteger(str_keys, str_teleport_xhair, 0x0);
		TELEPORT_MAP_KEY = iniReader.ReadInteger(str_keys, str_teleport_map, 0x0);
		MENU_KEY = iniReader.ReadInteger(str_keys, str_menu, 0x0);
		SPEEDHACK_KEY = iniReader.ReadInteger(str_keys, str_speedhack, 0x0);
		value_Speedhack = iniReader.ReadFloat(str_speedhack, str_ratio, 1.f);

		for (int i = 0; i < MAX_TELEPORTS; i++) {
			warp w = warps[i];
			w.key = iniReader.ReadInteger(str_keys, (char*)CONF_TELEPORT_DST_NAMES[i], 0x0);
			w.loaded = false;
			// very important one!!!
			warps[i] = w;
			// !!!
		}

		// init blacklist & whitelist from config file
		char* blist = (char*)iniReader.ReadString(str_lists, str_blacklist, "");
		stringsplit(blist, "|", blacklist);

		char* wlist = (char*)iniReader.ReadString(str_lists, str_whitelist, "");
		stringsplit(wlist, "|", whitelist);

		color_npc_friendly = iniReader.ReadInteger(str_colors, str_npc_friendly, -7282544);
		color_npc_hostile = iniReader.ReadInteger(str_colors, str_npc_hostile, -1973791);
		color_player_friendly = iniReader.ReadInteger(str_colors, str_player_friendly, -16719391);
		color_player_rogue = iniReader.ReadInteger(str_colors, str_player_rogue, -3394919);
		color_player_blacklisted = iniReader.ReadInteger(str_colors, str_player_blacklisted, -466880);

	}
	catch (...) { return false; }

	Speedhack::Setup();

	res_x = ImGui::GetIO().DisplaySize.x;
	res_y = ImGui::GetIO().DisplaySize.y;
	// Find the index module.
	// RecoilBaseFinal
	// "TheDivision.exe"+03D879B8 -> 348 -> 98 -> 2c0 -> 0

	g_is_init = true;

	return true;
}


constexpr int COLUMN_OFFSET = 200;
void cheat_tick(void) {

	if (g_is_init == false) {
		return;
	}

	if (GetAsyncKeyState(SPEEDHACK_KEY) < 0 && !speedhack_key_pressed) {
		G_Speedhack = !G_Speedhack;
		speedhack_key_pressed = true;
	}
	if (GetAsyncKeyState(SPEEDHACK_KEY) == 0 && speedhack_key_pressed) {
		speedhack_key_pressed = false;
	}

	if (G_Speedhack) {
		Speedhack::SetSpeed(value_Speedhack);
	}
	else {
		Speedhack::SetSpeed(1.f);
	}


	mat4 world = mat4_transpose(read_memory<mat4>(g_base_ptr + OFF_VIEWMATRIX));
	float hx = res_x / 2.0f;
	float hy = res_y / 2.0f;

	uintptr_t index_ptr = read_memory<uintptr_t>(g_base_ptr + OFF_INDEXMODULE);
	if (index_ptr != index_ptr || index_ptr == 0) return;
	uintptr_t index_arr = read_memory<uintptr_t>(index_ptr + 0x98);


	// Read out the indices.
	for (int i = 0; i < AtributeIndexMax; ++i) {
		g_indices[i] = read_memory<int>(read_memory<uintptr_t>(index_arr + i * 8) + 0x50);
	}

	uintptr_t rlc_ptr = read_memory<uintptr_t>(g_base_ptr + OFF_RLCLIENT);

	uintptr_t wrd_ptr = read_memory<uintptr_t>(rlc_ptr + 0x120);

	uintptr_t obj_ptr = read_memory<uintptr_t>(wrd_ptr + 0x28);

	int ent_cur = read_memory<int>(obj_ptr + 0x448);
	if (ent_cur < 1) return;
	// std::cout << "entity array ptr\n";
	uintptr_t ent_arr = read_memory<uintptr_t>(obj_ptr + 0x440);

	// very important to tell if the current entity number is 0 or game crashes
	uintptr_t player_ptr = read_memory<uintptr_t>(ent_arr + 0x0);
	if (player_ptr != player_ptr || player_ptr == 0) return;
	uintptr_t info_ptr0 = read_memory<uintptr_t>(player_ptr + 0x528);

	uintptr_t info_ptr1 = read_memory<uintptr_t>(info_ptr0 + 0x28);

	// std::cout << "Info array ptr\n";
	uintptr_t info_arr = read_memory<uintptr_t>(info_ptr1 + 0x78);
	

	ent_cur = ent_cur < MAX_ENTITIES ? ent_cur : MAX_ENTITIES;

	int ent_n = 0;
	int player_n = 0;

	for (int i = 0; i < ent_cur; i++) {
		entity e;
		e.ptr = read_memory<uintptr_t>(ent_arr + i * 0x08);

		// get name
		try {
			char buf;
			// std::cout << "name: ";
			for (int j = 0; j < sizeof(e.name); j++) {
				buf = read_memory<char>(e.ptr + 0x370 + j);
				if (buf == 0x0 || buf == 0x25) break;
				// std::cout << buf;
				e.name[j] = buf;
			}
			// std::cout << "\n";
		}
		catch (const char* msg) {
			// std::cout << msg;
			e.name[0] = 0x3F; e.name[1] = 0x0;
		}

		// get attributes
		{
			e.level = read_memory<int>(e.ptr + 0x3D0);
			// e.type = read_memory<char>(e.ptr + 0x3A4);
			e.is_player = read_memory<byte>(e.ptr + 0x3A4) == 1;
			e.is_gadget = read_memory<byte>(e.ptr + 0x354) == 1;
			e.is_human = read_memory<byte>(e.ptr + 0x400) == 1;
			e.is_friendly = read_memory<byte>(e.ptr + 0x748) == 1;
			e.is_rogue = read_memory<byte>(e.ptr + 0x75C) == 1;
			if (e.level < 1 || e.is_gadget == true || !e.is_human || strcmp(e.name, "") == 0 || strcmp(e.name, "Civilian") == 0) {
				continue;
			}
		}

		player_n += e.is_player;

		std::cout << "player position\n";
		e.pos = read_memory<vec3>(e.ptr + 0x70);
		std::cout << "x: " << e.pos.x << " y: " << e.pos.y << " z: " << e.pos.z << "\n";

		uintptr_t bone0 = read_memory<uintptr_t>(e.ptr + 0x1D0);
		if (bone0 == 0) continue;
		uintptr_t bptr = read_memory<uintptr_t>(bone0 + 0x1460);
		if (bptr == 0) continue;
		std::cout << "bone ptr: " << bptr;

		// get skeleton pos
		{
			e.torso = get_bone_pos(bptr, 0);
			e.head = get_bone_pos(bptr, 5);
			e.belly = get_bone_pos(bptr, 1);
			e.left_shoulder = get_bone_pos(bptr, 7);
			e.left_elbow = get_bone_pos(bptr, 8);
			e.left_hand = get_bone_pos(bptr, 11);
			e.left_thigh = get_bone_pos(bptr, 73);
			e.left_knee = get_bone_pos(bptr, 74);
			e.left_foot = get_bone_pos(bptr, 76);
			e.right_shoulder = get_bone_pos(bptr, 37);
			e.right_elbow = get_bone_pos(bptr, 38);
			e.right_hand = get_bone_pos(bptr, 41);
			e.right_thigh = get_bone_pos(bptr, 81);
			e.right_knee = get_bone_pos(bptr, 82);
			e.right_foot = get_bone_pos(bptr, 84);
			e.neck = get_bone_pos(bptr, 4);
		}

		if (e.head.x == 0 && e.head.y == 0 && e.head.z == 0) {
			e.head = e.pos;
		}

		if (strcmp(e.name, "Drone") == 0) {
			e.head = e.torso;
		}

		uintptr_t hptr = read_memory<uintptr_t>(e.ptr + 0x5D8);
		e.hp_cur = read_memory<int>(hptr + 0xA8);
		e.hp_max = read_memory<int>(hptr + 0xAC);

		if (e.hp_cur == 0 && !e.is_player) {
			continue;
		}

		entitylist[ent_n++] = e;

		// ImGui::Text("name: %s friendly %d", name, is_friendly);

		
	}

	auto draw = ImGui::GetBackgroundDrawList();

	if (G_ESP) {
		for (int i = 0; i < ent_n; i++) {

			if (i == 0) continue;

			entity e = entitylist[i];

			ImVec2 head_pos = w2s(e.head, world, hx, hy);
			ImVec2 neck_pos = w2s(e.neck, world, hx, hy);
			ImVec2 torso_pos = w2s(e.torso, world, hx, hy);
			ImVec2 belly_pos = w2s(e.belly, world, hx, hy);

			ImVec2 left_shoulder_pos = w2s(e.left_shoulder, world, hx, hy);
			ImVec2 left_elbow_pos = w2s(e.left_elbow, world, hx, hy);
			ImVec2 left_hand_pos = w2s(e.left_hand, world, hx, hy);
			ImVec2 left_thigh_pos = w2s(e.left_thigh, world, hx, hy);
			ImVec2 left_knee_pos = w2s(e.left_knee, world, hx, hy);
			ImVec2 left_foot_pos = w2s(e.left_foot, world, hx, hy);

			ImVec2 right_shoulder_pos = w2s(e.right_shoulder, world, hx, hy);
			ImVec2 right_elbow_pos = w2s(e.right_elbow, world, hx, hy);
			ImVec2 right_hand_pos = w2s(e.right_hand, world, hx, hy);
			ImVec2 right_thigh_pos = w2s(e.right_thigh, world, hx, hy);
			ImVec2 right_knee_pos = w2s(e.right_knee, world, hx, hy);
			ImVec2 right_foot_pos = w2s(e.right_foot, world, hx, hy);

			ImVec2 screen_top = w2s(vec3_set(e.head.x, e.head.y + 0.25f, e.head.z), world, hx, hy);
			ImVec2 left_bottom = w2s(vec3_set(e.left_foot.x, e.left_foot.y - 0.25f, e.left_foot.z), world, hx, hy);
			ImVec2 right_bottom = w2s(vec3_set(e.right_foot.x, e.right_foot.y - 0.25f, e.right_foot.z), world, hx, hy);
			ImVec2 screen_bot = ImVec2((left_bottom.x + right_bottom.x) * 0.5f, left_bottom.y < right_bottom.y ? left_bottom.y : right_bottom.y);

			float y = screen_top.y;
			float h = screen_bot.y - screen_top.y;
			float w = h * 0.5f;
			float x = screen_top.x - w * 0.5f;

			if (h < 1.0 || (x <= 0 && screen_top.y <= 0)) {
				continue;
			}

			ImColor color(0, 0, 0);
			if (e.is_player) {
				if (is_blacklisted(e.name)) {
					color = color_player_blacklisted;
					// color = ImColor(64, 224, 248);
					// 40E0F8FF
				}
				else
				{
					if (is_whitelisted(e.name) || !e.is_rogue) {
						color = color_player_friendly;
						// color = ImColor(255, 255, 0);
						// FFFF00FF
					}
					else {
						color = color_player_rogue;
						// color = ImColor(153, 50, 204);
						// 9932CCFF
					}
				}

			}
			else {
				if (e.is_friendly) {
					color = color_npc_friendly;
					// color = ImColor(144, 224, 144);
					// 90E090FF
				}
				else {
					color = color_npc_hostile;
					// color = ImColor(225, 225, 225);
					// E1E1E1FF
				}
			}

			if (G_ESP) draw->AddText(ImVec2(screen_bot.x - strlen(e.name) / 2 * 7, screen_top.y - 20), color, e.name);

			if ((G_Box_player && e.is_player) || (G_Box_npc && !e.is_player)) {
				// a player is always friendly regardless of being rogue or not
				draw->AddRect(ImVec2(x, y), ImVec2(x + w, screen_bot.y), color, 0.F, 0);
			}

			if ((G_Skeleton_player && e.is_player) || (G_Skeleton_npc && !e.is_player))
			{
				if (e.is_human) {

					if (head_pos.x > res_x || head_pos.y > res_y) continue;

					draw->AddLine(head_pos, neck_pos, color, 1.f);
					draw->AddLine(neck_pos, belly_pos, color, 1.f);

					draw->AddLine(neck_pos, left_shoulder_pos, color, 1.f);
					draw->AddLine(left_shoulder_pos, left_elbow_pos, color, 1.f);
					draw->AddLine(left_elbow_pos, left_hand_pos, color, 1.f);
					draw->AddLine(belly_pos, left_thigh_pos, color, 1.f);
					draw->AddLine(left_thigh_pos, left_knee_pos, color, 1.f);
					draw->AddLine(left_knee_pos, left_foot_pos, color, 1.f);

					draw->AddLine(neck_pos, right_shoulder_pos, color, 1.f);
					draw->AddLine(right_shoulder_pos, right_elbow_pos, color, 1.f);
					draw->AddLine(right_elbow_pos, right_hand_pos, color, 1.f);
					draw->AddLine(belly_pos, right_thigh_pos, color, 1.f);
					draw->AddLine(right_thigh_pos, right_knee_pos, color, 1.f);
					draw->AddLine(right_knee_pos, right_foot_pos, color, 1.f);

				}
			}

			if (G_Health && e.hp_cur > 0) {
				draw->AddRectFilled(ImVec2(x, y - 3), ImVec2(x + w * (float)((float)e.hp_cur / (float)e.hp_max), y - 1), ImColor(255, 235, 42));
			}
			if ((G_Snapline_player && e.is_player) || (G_Snapline_npc && !e.is_player)) {
				draw->AddLine(screen_bot, ImVec2((float)res_x / 2, res_y), color);
			}
		}

	}

	if (GetForegroundWindow() != FindWindowA(NULL, "Tom Clancy's The Division")) return;
	

	if (G_RPM) {
		set_index_val(info_arr, RPM, value_RPM);
	}

	if (G_Recoil) {
		write_memory<float>(g_base_ptr + 0x3F8A2F4, 0);
		set_index_val(info_arr, RecoilBase, 0.f);
		set_index_val(info_arr, RecoilMin, 0.f);
		set_index_val(info_arr, RecoilMax, 0.f);
		set_index_val(info_arr, RecoilClimbTimeMS, 0.f);
		set_index_val(info_arr, RecoilIncreasePerBullet, 0.f);
		set_index_val(info_arr, RecoilRecoveryPerSecond, 0.f);
		set_index_val(info_arr, RecoilRecoveryTimeMS, 0.f);
		set_index_val(info_arr, RecoilResetTimeMS, 0.f);
		set_index_val(info_arr, HorizontalRecoilBorderLeft, 0.f);
		set_index_val(info_arr, HorizontalRecoilBorderRight, 0.f);
		set_index_val(info_arr, HorizontalRecoilLeft, 0.f);
		set_index_val(info_arr, HorizontalRecoilRecoveryTimeMS, 0.f);
		set_index_val(info_arr, HorizontalRecoilRight, 0.f);
		set_index_val(info_arr, HorizontalRecoilTimeMS, 0.f);
		set_index_val(info_arr, WeaponRecoilKickModBonus, 0.f);
		set_index_val(info_arr, NormalizedWeaponRecoilKickModBonus, 0.f);

		set_index_val(info_arr, AimSwayMinHorizontal, 0.f);
		set_index_val(info_arr, AimSwayMaxHorizontal, 0.f);
		set_index_val(info_arr, AimSwayMinVertical, 0.f);
		set_index_val(info_arr, AimSwayMaxVertical, 0.f);
		set_index_val(info_arr, AimSwaySpeedModifier, 0.f);

	}

	if (G_Spread) {
		set_index_val(info_arr, SpreadMin, 0.f);
		set_index_val(info_arr, SpreadMax, 0.f);
		set_index_val(info_arr, AimSpreadMax, 0.f);
		set_index_val(info_arr, AimSpreadMin, 0.f);
		set_index_val(info_arr, CoverAimSpreadMax, 0.f);
		set_index_val(info_arr, CoverAimSpreadMin, 0.f);
		set_index_val(info_arr, CoverSpreadMax, 0.f);
		set_index_val(info_arr, CoverSpreadMin, 0.f);
		set_index_val(info_arr, SpreadMovementMod, 0.f);
		set_index_val(info_arr, SpreadIncreaseSpeed, 0.f);
		set_index_val(info_arr, SpreadIncreaseTimeMS, 0.f);
		// set_index_val(info_arr, SpreadReductionSpeed, 999.f);
	}

	if (G_Reload) {
		set_index_val(info_arr, ReloadTimeMS, 1.f);
		set_index_val(info_arr, EmptyClipFirstRoundReloadTimeMS, 1.f);
		set_index_val(info_arr, InitialShellReloadTimeMS, 1.f);
	}

	if (G_Teleport) {
		uintptr_t pos_ptr0 = read_memory<uintptr_t>(player_ptr + 0x1D0);
		if (pos_ptr0 == 0) return;
		uintptr_t pos_ptr1 = read_memory<uintptr_t>(pos_ptr0 + 0x220);
		if (pos_ptr1 == 0) return;
		uintptr_t pos_ptr = read_memory<uintptr_t>(pos_ptr1 + 0x278);
		if (pos_ptr == 0) return;

		vec3 cur_pos = read_memory<vec3>(player_ptr + OFF_WARP_POS);
		snprintf(TELEPORT_PLAYER_CURRENT_COORDS, sizeof(TELEPORT_PLAYER_CURRENT_COORDS), "|%f|%f|%f|", cur_pos.x, cur_pos.y, cur_pos.z);

		TELEPORT_XHAIR_KEY = iniReader.ReadInteger(str_keys, str_teleport_xhair, 0x0);
		TELEPORT_MAP_KEY = iniReader.ReadInteger(str_keys, str_teleport_map, 0x0);


		if (GetAsyncKeyState(TELEPORT_XHAIR_KEY) < 0 && !teleport_xhair_key_pressed) {

			uintptr_t xhair_ptr = read_memory<uintptr_t>(player_ptr + 0x630);
			if (xhair_ptr == 0) return;
			vec3 TraceEnd = read_memory<vec3>(xhair_ptr + 0x31EC);

			write_memory<vec3>(pos_ptr + OFF_WARP_POS, TraceEnd);

			teleport_xhair_key_pressed = true;
		}
		if (GetAsyncKeyState(TELEPORT_XHAIR_KEY) == 0 && teleport_xhair_key_pressed) {
			teleport_xhair_key_pressed = false;
		}

		if (GetAsyncKeyState(TELEPORT_MAP_KEY) < 0) {

			uintptr_t map_ptr = read_memory<uintptr_t>(obj_ptr + 0x320);
			if (map_ptr == 0) return;
			vec3 waypoint = read_memory<vec3>(map_ptr + 0x80);
			if (waypoint.x != 0.f && waypoint.z != 0.f) {
				tmp = waypoint;
				tmp.y += 0.5f;
			}

			vec3 pos = read_memory<vec3>(pos_ptr + OFF_WARP_POS);
			if (tmp.x != -1 && tmp.y != -1 && tmp.z != -1) {
				if ((pos.x != tmp.x && pos.z != tmp.z) || (waypoint.x == 0 && waypoint.z == 0 && pos.x == tmp.x && pos.z == tmp.z)) {
					write_memory<vec3>(pos_ptr + OFF_WARP_POS, tmp);
				}
			}

		}

		for (int i = 0; i < MAX_TELEPORTS; i++) {
			warp w = warps[i];

			char* key = get_vk_name(w.key);
			if (strcmp(key, "?") == 0) continue;

			if (GetAsyncKeyState(w.key) < 0 || w.loaded) {
				w.loaded = false;
				try {
					char* buf = iniReader.ReadString(str_teleports, (char*)CONF_TELEPORT_DST_NAMES[i], 0x0);
					std::string delimiter = "|";
					std::vector<std::string> results;
					stringsplit(buf, delimiter, results);
					if (results.size() > 2) {
						vec3 p = vec3_set(stof(results[0]), stof(results[1]), stof(results[2]));
						w.pos = p;
						// std::cout << "pressed" << std::endl;
						p.y += 0.1f;
						// Division dev is literally retarded y is actually z here
						if (p.x != 0.f && p.y != 0.1f && p.z != 0.f) {
							write_memory<vec3>(pos_ptr + OFF_WARP_POS, p);
						}
					}
					else {
						w.pos = vec3_zero();
					}
				}
				catch (...) {
					w.pos = vec3_zero();
				}
			}
			warps[i] = w;


		}

	}


}



HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{

	if (!init)
	{

		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);

	}

	DoStyle();

	if (GetAsyncKeyState(MENU_KEY) < 0 && !menu_key_pressed) {
		show_menu = !show_menu;
		menu_key_pressed = true;
	}
	if (GetAsyncKeyState(MENU_KEY) == 0 && menu_key_pressed) {
		menu_key_pressed = false;
	}


	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (show_menu) {
		
		ImGui::Begin("Envia", nullptr, ImGuiWindowFlags_NoResize);

		ImGui::Columns(2);
		ImGui::SetColumnOffset(1, COLUMN_OFFSET);
		static int tab = 0;

		
		if (!g_is_init) {
			if (game_init() == false) {
				ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));
				char* text = (char*)"Failed to init";
				ImGui::SetCursorPosX(((float)COLUMN_OFFSET - ImGui::CalcTextSize(text).x) * 0.5f);
				ImGui::Text(text);
				ImGui::PopStyleColor();
			}
		}
		else {
			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 204, 51, 255));
			char* text = (char*)"Game module initialized";
			ImGui::SetCursorPosX(((float)COLUMN_OFFSET - ImGui::CalcTextSize(text).x) * 0.5f);
			ImGui::Text(text);
			ImGui::PopStyleColor();

			ImGui::Spacing();
			if (ImGui::Button("Weapon", ImVec2(COLUMN_OFFSET - 30, 40)))
				tab = 1;

			ImGui::Spacing();
			if (ImGui::Button("ESP", ImVec2(COLUMN_OFFSET - 30, 40)))
				tab = 2;

			ImGui::Spacing();
			if (ImGui::Button("Teleport", ImVec2(COLUMN_OFFSET - 30, 40)))
				tab = 3;

			ImGui::Spacing();
			if (ImGui::Button("Misc", ImVec2(COLUMN_OFFSET - 30, 40)))
				tab = 4;

			// float res_x = , res_y = ImGui::GetIO().DisplaySize.y;
			// ImGui::Text("rpm %x, recoil %x, spread %x", g_indices[RPM], g_indices[RecoilBase], g_indices[SpreadMax]);
		}
		
		ImGui::NextColumn();
		{
			if (g_is_init) {
				switch (tab) {
				case 1:
					ImGui::Text("Handling");

					ImGui::Checkbox("Recoil + Sway", &G_Recoil);
					ImGui::Checkbox("Spread", &G_Spread);
					ImGui::Checkbox("Reload", &G_Reload);
					ImGui::Text("Attributes");

					ImGui::Checkbox("RPM", &G_RPM);
					if (G_RPM) {
						ImGui::SameLine();
						ImGui::SliderFloat("value", &value_RPM, 1000.f, 500000.f);
					}
					break;
				case 2:
					ImGui::Text("Visuals");

					ImGui::Checkbox("Enable ESP", &G_ESP);

					ImGui::Checkbox("Health", &G_Health);
					if (ImGui::CollapsingHeader("Bounding box")) {
						ImGui::Checkbox("Player box", &G_Box_player);
						ImGui::Checkbox("NPC box", &G_Box_npc);
					}
					if (ImGui::CollapsingHeader("Skeleton"))
					{
						ImGui::Checkbox("Player skeleton", &G_Skeleton_player);
						ImGui::Checkbox("NPC skeleton", &G_Skeleton_npc);

					}
					if (ImGui::CollapsingHeader("Snapline")) {
						ImGui::Checkbox("Player snapline", &G_Snapline_player);
						ImGui::Checkbox("NPC snapline", &G_Snapline_npc);
					}
					break;
				case 3:
					ImGui::Text("Teleport");

					ImGui::Checkbox("Enable", &G_Teleport);
					ImGui::Spacing();
					ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 153, 18, 255));
					ImGui::SameLine();
					ImGui::Text(" %s -> xhair\n %s -> waypoint on map", get_vk_name(TELEPORT_XHAIR_KEY), get_vk_name(TELEPORT_MAP_KEY));
					ImGui::PopStyleColor();
					ImGui::Spacing();
					ImGui::Text("Current Coords: %s", TELEPORT_PLAYER_CURRENT_COORDS);
					if (ImGui::Button("Copy to clipboard")) {
						toClipboard(TELEPORT_PLAYER_CURRENT_COORDS);
					}

					if (ImGui::BeginMenu("Load Position")) {
						for (int i = 0; i < MAX_TELEPORTS; i++) {
							char* key = get_vk_name(warps[i].key);
							if (strcmp(key, "?") == 0) continue;
							if (ImGui::Button(key)) {
								warps[i].loaded = true;
							}
						}
						ImGui::EndMenu();
					}

					if (ImGui::BeginMenu("Save Position")) {
						for (int i = 0; i < MAX_TELEPORTS; i++) {
							char* key = get_vk_name(warps[i].key);
							if (strcmp(key, "?") == 0) continue;
							if (ImGui::Button(key)) {
								try {
									iniWriter.WriteString((char*)"Teleports", (char*)CONF_TELEPORT_DST_NAMES[i], TELEPORT_PLAYER_CURRENT_COORDS);
								}
								catch (...) {}
							}
						}
						ImGui::EndMenu();
					}

					break;

				case 4:

					ImGui::Text("Blacklist & whitelist");

					if (ImGui::Button("Update")) {
						try {
							char* blist = (char*)iniReader.ReadString(str_lists, str_blacklist, "");
							stringsplit(blist, "|", blacklist);

							char* wlist = (char*)iniReader.ReadString(str_lists, str_whitelist, "");
							stringsplit(wlist, "|", whitelist);
						}
						catch (...) {
							ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));
							ImGui::SameLine();
							ImGui::Text("Update failed");
							ImGui::PopStyleColor();
						}
					}
					ImGui::Text("Settings");

					if (ImGui::Button("Save Settings")) {
						try {
							iniWriter.WriteBoolean(str_settings, (char*)"ESP", G_ESP);
							iniWriter.WriteBoolean(str_settings, (char*)"Box_npc", G_Box_npc);
							iniWriter.WriteBoolean(str_settings, (char*)"Box_player", G_Box_player);
							iniWriter.WriteBoolean(str_settings, (char*)"Skeleton_npc", G_Skeleton_npc);
							iniWriter.WriteBoolean(str_settings, (char*)"Skeleton_player", G_Skeleton_player);
							iniWriter.WriteBoolean(str_settings, (char*)"Snapline_npc", G_Snapline_npc);
							iniWriter.WriteBoolean(str_settings, (char*)"Snapline_player", G_Snapline_player);
							iniWriter.WriteBoolean(str_settings, (char*)"Recoil", G_Recoil);
							iniWriter.WriteBoolean(str_settings, (char*)"Spread", G_Spread);
							iniWriter.WriteBoolean(str_settings, (char*)"Reload", G_Reload);
							iniWriter.WriteBoolean(str_settings, (char*)"RPM", G_RPM);
							iniWriter.WriteBoolean(str_settings, (char*)"Teleport", G_Teleport);
							iniWriter.WriteBoolean(str_settings, (char*)"Health", G_Health);
							iniWriter.WriteBoolean(str_settings, str_speedhack, G_Speedhack);
						}
						catch (...) {
							ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));
							ImGui::SameLine();
							ImGui::Text("Save settings failed");
							ImGui::PopStyleColor();
						}
					}

					ImGui::Spacing();
					if (ImGui::BeginMenu("Colors")) {
						ImGui::ColorEdit4("NPC friendly", (float*)&color_npc_friendly);
						ImGui::ColorEdit4("NPC hostile", (float*)&color_npc_hostile);
						ImGui::ColorEdit4("Player friendly", (float*)&color_player_friendly);
						ImGui::ColorEdit4("Player rogue", (float*)&color_player_rogue);
						ImGui::ColorEdit4("Player blacklisted", (float*)&color_player_blacklisted);
						ImGui::EndMenu();
					}

					if (ImGui::Button("Save Colors")) {
						try {
							iniWriter.WriteInteger(str_colors, str_npc_friendly, color_npc_friendly);
							iniWriter.WriteInteger(str_colors, str_npc_hostile, color_npc_hostile);
							iniWriter.WriteInteger(str_colors, str_player_friendly, color_player_friendly);
							iniWriter.WriteInteger(str_colors, str_player_rogue, color_player_rogue);
							iniWriter.WriteInteger(str_colors, str_player_blacklisted, color_player_blacklisted);
						}
						catch (...) {
							ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));
							ImGui::SameLine();
							ImGui::Text("Save colors failed");
							ImGui::PopStyleColor();
						}
					}

					ImGui::Checkbox(str_speedhack, &G_Speedhack);
					ImGui::SliderFloat("Ratio", &value_Speedhack, 0.125f, 64.f);
					break;

				default:
					/*
					ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 204, 51, 255));
					char* text = (char*)"A small internal tool made by t0x?";
					ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(text).x + COLUMN_OFFSET) * 0.5f);
					ImGui::Text(text);
					ImGui::PopStyleColor();
					*/
					break;
				}
			}
		}

		ImGui::End();

	}

	try {
		cheat_tick();
	}
	catch (...) {}
	
	ImGui::Render();
	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());



	return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
	// AllocConsole();
	// HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// SMALL_RECT srctWindow = { 0, 0, 80, 25 };
	// SetConsoleWindowInfo(hConsole, TRUE, &srctWindow);
	// FILE* f;
	// freopen_s(&f, "CONOUT$", "w", stdout);
	// std::cout << "Debug information starts:\n";
	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)&oPresent, hkPresent);
			init_hook = true;
		}
	} while (!init_hook);
	return TRUE;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}