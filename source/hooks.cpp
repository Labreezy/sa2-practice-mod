#include "hooks.h"

// restart function address stolen from https://github.com/StarlitLuna/sa2-story-style-upgrades
FunctionHook<void> hRestartLevel((intptr_t)0x43C370);
// kart_delete function (thank you tenzit)
FunctionHook<void> hkart_delete((intptr_t)0x61A910);

static StdcallFunctionHook<LRESULT, HWND, UINT, WPARAM, LPARAM>* wndProcHook = new StdcallFunctionHook<LRESULT, HWND, UINT, WPARAM, LPARAM>(WndProc);
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// i couldn't figure out how to use the extern keyword :broken_heart:
UpgradeRemover* g_upgradeR = nullptr;
Settings* g_settings = nullptr; 
  
// TODO: fix the window breaking when resizing
// (at least, thats where i think the resizing breaking the window is happening)
LRESULT __stdcall wndProc_h(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam) {

	if (ImGui_ImplWin32_WndProcHandler(hwnd, umsg, wParam, lParam)) {
		return true;
	}
	return wndProcHook->Original(hwnd, umsg, wParam, lParam);
}

void initHooks(UpgradeRemover* u, Settings* s) {
	wndProcHook->Hook(wndProc_h);
	hRestartLevel.Hook(RestartLevel);
	hkart_delete.Hook(kart_delete);

	g_upgradeR = u;
	g_settings = s;
}

// function hooks listed here can used by multiple tabs
void RestartLevel() {
	if (g_settings->ppSkipToggleStatus()) {
		ppSkipTimer = 0;
	}
	
	hRestartLevel.Original();
}

// called when exiting the level
void kart_delete() {
	hkart_delete.Original();
	if (g_settings->ppSkipToggleStatus()) {
		ppSkipTimer = 0;
	}
}