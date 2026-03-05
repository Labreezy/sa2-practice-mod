#include "hooks.h"


static StdcallFunctionHook<LRESULT, HWND, UINT, WPARAM, LPARAM>* wndProcHook = new StdcallFunctionHook<LRESULT, HWND, UINT, WPARAM, LPARAM>(WndProc);
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT __stdcall wndProc_h(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam) {

	if (ImGui_ImplWin32_WndProcHandler(hwnd, umsg, wParam, lParam)) {
		return true;
	}
	return wndProcHook->Original(hwnd, umsg, wParam, lParam);
}

void initHooks() {
	wndProcHook->Hook(wndProc_h);

}