#pragma once
#include "objs.h"
#include "stdafx.h"

HWND parent;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);//可以使GetMessage返回0  
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

BOOL RegisterWindow()
{
	WNDCLASSEX wce = { 0 };
	wce.cbSize = sizeof(wce);
	wce.cbClsExtra = 0;
	wce.cbWndExtra = 0;
	wce.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wce.hCursor = NULL;
	wce.hIcon = NULL;
	wce.hIconSm = NULL;
	wce.hInstance = NULL;
	wce.lpfnWndProc = WndProc;
	wce.lpszClassName = "DllMain";
	wce.lpszMenuName = NULL;
	wce.style = CS_HREDRAW | CS_VREDRAW | CS_GLOBALCLASS;
	ATOM nAtom = RegisterClassEx(&wce);
	if (nAtom == 0)
		return FALSE;
	return true;
}

//展示和更新主窗口
void Display(HWND hwnd) {
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
}

void  createWindow() {

	HWND window_ = CreateWindow("DllMain", "子窗口",
		WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 800, 400,
		parent, NULL, NULL, NULL);
	
	Display(window_);


}

//解决闪烁的问题
void resolveBlink(HWND hwnd) {
	if (::IsWindow(hwnd)) {
		DWORD style = GetWindowLong(hwnd, GWL_STYLE);
		style |= WS_CLIPCHILDREN;
		SetWindowLong(hwnd, GWL_STYLE, style);
	}

}

//thread proc
void entrance()
{
	MSG messages;
	RegisterWindow();
	createWindow();
	while (GetMessage(&messages, NULL, 0, 0))
	{
		TranslateMessage(&messages);
		DispatchMessage(&messages);
	}
}
//entrance
void createProcess(HWND hwnd) {
	parent = hwnd;
	resolveBlink(hwnd);
	entrance();
}
