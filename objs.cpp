#pragma once
#include "objs.h"
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "WPFPageHost.h"



#ifdef _MANAGED
#pragma managed(push, off)
#endif

#ifdef _MANAGED
#pragma managed(pop)
#endif

HWND mqlWindow;
HWND parentWindow;



void WPFButtonClicked(Object ^sender, MyApplicationEventArgs ^args)
{

	System:: Windows::MessageBox::Show(args->Actor);
}

void GridMoved(Object ^sender, Point ^p) {
	RECT rect;
	GetWindowRect(parentWindow, &rect);
	MapWindowPoints(HWND_DESKTOP, mqlWindow, (LPPOINT)&rect, 2);
	MoveWindow(parentWindow, rect.left + p->X, rect.top + p->Y, 240, 140, true);
}

//get hwnd of a WPF
HWND GetHwnd(HWND pa, int x, int y, int width, int height)
{
	System::Windows::Interop::HwndSourceParameters^ sourceParams = gcnew System::Windows::Interop::HwndSourceParameters(
		"hi" // NAME
	);
	sourceParams->PositionX = x;
	sourceParams->PositionY = y;
	sourceParams->Height = height;
	sourceParams->Width = width;
	sourceParams->ParentWindow = System::IntPtr(pa);
	sourceParams->WindowStyle =  WS_VISIBLE | WS_CHILD; // style
	System::Windows::Interop::HwndSource^ source = gcnew System::Windows::Interop::HwndSource(*sourceParams);

	WPFPage ^myPage = gcnew WPFPage(width, height);
	//Assign a reference to the WPF page and a set of UI properties to a set of static properties in a class
	//that is designed for that purpose.
	WPFPageHost::hostedPage = myPage;
	WPFPageHost::initBackBrush = myPage->Background;
	WPFPageHost::initFontFamily = myPage->DefaultFontFamily;
	myPage->OnButtonClicked += gcnew WPFPage::ButtonClickHandler(WPFButtonClicked);
	myPage->OnGridMoved += gcnew WPFPage::GridMoveHandler(GridMoved);
	source->RootVisual = myPage;
	return (HWND)source->Handle.ToPointer();
}




LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);//����ʹGetMessage����0  
		break;
	case WM_CREATE:
		//GetClientRect(hWnd, &rect);
		HWND hwnd = GetHwnd(hWnd, 0, 0, 240, 140);
		//DWORD error = GetLastError();
		//CreateDataDisplay(hWnd, 275, rect.right - 375, 375);
		//CreateRadioButtons(hWnd);;
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


//չʾ�͸���������
void Display(HWND hwnd) {
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
}

void  createWindow() {
	HWND window_ = CreateWindow("DllMain", "�Ӵ���",
		WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 240, 140,
		mqlWindow , NULL, NULL, NULL);
	

	parentWindow = window_;
	SetWindowLong(window_, GWL_STYLE, 0);
	Display(window_);

}

//�����˸������
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
