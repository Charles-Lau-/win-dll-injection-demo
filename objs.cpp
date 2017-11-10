#pragma once
#include "objs.h"
#include "stdafx.h"
#include <stdio.h>
#include <map>
#include <iostream>
#include "WPFPageHost.h"

using namespace std;

#ifdef _MANAGED
#pragma managed(push, off)
#endif

#ifdef _MANAGED
#pragma managed(pop)
#endif

#define WM_SHOUDONG_SWITCH (WM_USER + 0x0001)
HWND mqlWindow;
HWND parentWindow;



map<string, HWND> nameAndWindows;



//解决子窗口重叠问题
void resolveOverlapping(HWND hwnd) {
	if (::IsWindow(hwnd)) {
		DWORD style = GetWindowLong(hwnd, GWL_STYLE);
		style |= WS_CLIPSIBLINGS;
		SetWindowLong(hwnd, GWL_STYLE, style);
	}
}

LPCSTR StringToLPCSTR(String^ s) {
	return (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(s)).ToPointer();
}

void MarshalString(String^ s, string& os) {
	const char* chars = (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	System::Runtime::InteropServices::Marshal::FreeHGlobal(IntPtr((void*)chars));
}


HWND getWindowHWNDFromName(String^ s) {
	string a = "";
	MarshalString(s, a);
	return nameAndWindows[a];
}

void setWindowHWNDFromName(String^ s, HWND hwnd) {
	string a = "";
	MarshalString(s, a);
	nameAndWindows[a] = hwnd;
}

//展示和更新主窗口
void Display(HWND hwnd) {
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
}


BOOL RegisterWindow(LPCSTR name, WNDPROC messageDealing)
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
	wce.lpfnWndProc = messageDealing;
	wce.lpszClassName = name;
	wce.lpszMenuName = NULL;
	wce.style = CS_HREDRAW | CS_VREDRAW | CS_GLOBALCLASS;
	ATOM nAtom = RegisterClassEx(&wce);
	if (nAtom == 0)
		return FALSE;
	return true;
}


HWND createWindow(LPCSTR name, int x, int y, int width, int height) {
	HWND window_ = CreateWindow(name, "子窗口",
		WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_SYSMENU | WS_CLIPSIBLINGS, x, y, width, height,
		mqlWindow, NULL, NULL, NULL);


	SetWindowLong(window_, GWL_STYLE, WS_CLIPSIBLINGS);
	Display(window_);
	return window_;

}

//all below functions have something to do with advanced panel

void AdvanceWindowButtonClicked(Object ^sender, MyApplicationEventArgs ^args) {
	if (args->Actor == "panel") {
		if (args->Verb == "close") {
			DestroyWindow(getWindowHWNDFromName(args->Target));
			PostMessage(parentWindow, WM_SHOUDONG_SWITCH, 0, 0);
		}
	}
}


void GridMoved(Object ^sender, PanelMoveEventArgs ^args) {
	String^ subject = args->Actor;
	HWND target = NULL;


	if (subject == "main_panel")
		target = parentWindow;
	else
		target = getWindowHWNDFromName(subject);
	Point^ p = args->Location;
	RECT rect;
	GetWindowRect(target, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
	MapWindowPoints(HWND_DESKTOP, mqlWindow, (LPPOINT)&rect, 2);


	MoveWindow(target, rect.left + p->X, rect.top + p->Y, width , height , true);

}


HWND GetShouDongPingChangHwnd(HWND pa, int x, int y) {
	System::Windows::Interop::HwndSourceParameters^ sourceParams = gcnew System::Windows::Interop::HwndSourceParameters(
		"shoudong_panel" // NAME
	);
	sourceParams->PositionX = x;
	sourceParams->PositionY = y;
	sourceParams->ParentWindow = System::IntPtr(pa);
	sourceParams->WindowStyle = WS_VISIBLE | WS_CHILD; // style
	System::Windows::Interop::HwndSource^ source = gcnew System::Windows::Interop::HwndSource(*sourceParams);

	ShouDongPage ^myPage = gcnew ShouDongPage();
	//Assign a reference to the WPF page and a set of UI properties to a set of static properties in a class
	//that is designed for that purpose.
	ShouDongPageHost::hostedPage = myPage;
	ShouDongPageHost::initBackBrush = myPage->Background;
	ShouDongPageHost::initFontFamily = myPage->DefaultFontFamily;
	myPage->OnButtonClicked += gcnew ShouDongPage::ButtonClickHandler(AdvanceWindowButtonClicked);
	myPage->OnGridMoved += gcnew ShouDongPage::GridMoveHandler(GridMoved);
	source->RootVisual = myPage;
	return (HWND)source->Handle.ToPointer();
}

LRESULT CALLBACK shouDongPingChangWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);//可以使GetMessage返回0  
		break;
	case WM_CREATE:
		//GetClientRect(hWnd, &rect);
		HWND hwnd = GetShouDongPingChangHwnd(hWnd, 0, 0);
		resolveOverlapping(hwnd);
		//DWORD error = GetLastError();
		//CreateDataDisplay(hWnd, 275, rect.right - 375, 375);
		//CreateRadioButtons(hWnd);;
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void createAdvanceWindow(Object^ name) {
	MSG messages;
	String^ nameStr = (String^)name;
	LPCSTR nameLPC = StringToLPCSTR(nameStr);
	RegisterWindow(nameLPC, shouDongPingChangWndProc);
	RECT rect;
	GetWindowRect(parentWindow, &rect);
	MapWindowPoints(HWND_DESKTOP, mqlWindow, (LPPOINT)&rect, 2);
	HWND main = createWindow(nameLPC, rect.right, rect.top, 270, 300);
	setWindowHWNDFromName(nameStr, main);
	while (GetMessage(&messages, NULL, 0, 0)) {
		TranslateMessage(&messages);
		DispatchMessage(&messages);
	}
}

void createAdvanceProcess(String^ name) {
	System::Threading::Thread^  t = gcnew System::Threading::Thread(gcnew System::Threading::ParameterizedThreadStart(createAdvanceWindow));
	t->ApartmentState = System::Threading::ApartmentState::STA;
	t->Start(name);
}


void openAdvanceWindow(String^ type) {
	if (type == "shoudong_panel") {
		createAdvanceProcess("shoudong_panel");
	}
}

void closeAdvanceWindow(String^ type) {
	if (type == "shoudong_panel") {
		PostMessage(getWindowHWNDFromName(type), WM_CLOSE, 0, 0);
	}
}

void MainWindowButtonClicked(Object ^sender, MyApplicationEventArgs ^args)
{

	if (args->Actor == "advance_panel") {
		RECT rect;
		GetWindowRect(parentWindow, &rect);
		int width = rect.right - rect.left;
		int height = 0;
		if (args->Target == "advance")
			height = 600;
		else{
			height = 120;
		}
		MapWindowPoints(HWND_DESKTOP, mqlWindow, (LPPOINT)&rect, 2);
		MoveWindow(parentWindow, rect.left, rect.top, width, height, true);
	}
	else if (args->Actor == "advance_switch") {
		if (args->Verb == "open") {
			openAdvanceWindow(args->Target);
		}
		else if (args->Verb == "close") {
			closeAdvanceWindow(args->Target);
		}
	}
}

//get hwnd of a WPF
HWND GetMainHwnd(HWND pa, int x, int y)
{
	System::Windows::Interop::HwndSourceParameters^ sourceParams = gcnew System::Windows::Interop::HwndSourceParameters(
		"main" // NAME
	);
	sourceParams->PositionX = x;
	sourceParams->PositionY = y;
	sourceParams->ParentWindow = System::IntPtr(pa);
	sourceParams->WindowStyle =  WS_VISIBLE | WS_CHILD; // style
	System::Windows::Interop::HwndSource^ source = gcnew System::Windows::Interop::HwndSource(*sourceParams);

	MainPage^myPage = gcnew MainPage();
	//Assign a reference to the WPF page and a set of UI properties to a set of static properties in a class
	//that is designed for that purpose.
	MainPageHost::hostedPage = myPage;
	MainPageHost::initBackBrush = myPage->Background;
	MainPageHost::initFontFamily = myPage->DefaultFontFamily;
	myPage->OnButtonClicked += gcnew MainPage::ButtonClickHandler(MainWindowButtonClicked);
	myPage->OnGridMoved += gcnew MainPage::GridMoveHandler(GridMoved);
	source->RootVisual = myPage;
	return (HWND)source->Handle.ToPointer();
}




//message resolve for main window
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);//可以使GetMessage返回0  
		break;
	case WM_SHOUDONG_SWITCH:
		MainPageHost::hostedPage->switchShouDongOff();
	case WM_CREATE:
		//GetClientRect(hWnd, &rect);
		HWND hwnd = GetMainHwnd(hWnd, 0, 0);
		resolveOverlapping(hwnd);
		//DWORD error = GetLastError();
		//CreateDataDisplay(hWnd, 275, rect.right - 375, 375);
		//CreateRadioButtons(hWnd);;
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
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
	RegisterWindow("DllMain", WndProc);
	HWND main = createWindow("DllMain", 0, 0,270, 120);
	parentWindow = main;
	while (GetMessage(&messages, NULL, 0, 0))
	{
		TranslateMessage(&messages);
		DispatchMessage(&messages);
	}
}


void ThreadProc() {
	resolveBlink(mqlWindow);
	entrance();
}




//entrance
void createProcess(HWND hwnd) {
	mqlWindow = hwnd;
	System::Threading::Thread^  t = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(ThreadProc));
	t->ApartmentState = System::Threading::ApartmentState::STA;
	t->Start();
}
