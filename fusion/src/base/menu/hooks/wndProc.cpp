#include "../menu.h"

#include "../../../../ext/imgui/imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef LRESULT(CALLBACK* template_WndProc) (HWND, UINT, WPARAM, LPARAM);
template_WndProc original_wndProc;
LRESULT CALLBACK hook_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_KEYDOWN)
	{
		if (wParam == Menu::Keybind)
			Menu::Open = !Menu::Open;
		if (wParam == VK_ESCAPE && Menu::Open)
			Menu::Open = false;
	}

	if (Menu::Open && Menu::Initialized)
	{
		ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam);
		return true;
	}

	return CallWindowProc(original_wndProc, hwnd, msg, wParam, lParam);
}

void Menu::Hook_wndProc()
{
	original_wndProc = (template_WndProc)SetWindowLongPtr(Menu::HandleWindow, GWLP_WNDPROC, (LONG_PTR)hook_WndProc);
}

void Menu::Unhook_wndProc()
{
	SetWindowLongPtr(Menu::HandleWindow, GWLP_WNDPROC, (LONG_PTR)original_wndProc);
}