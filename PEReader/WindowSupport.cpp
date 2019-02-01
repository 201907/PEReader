#include "WindowSupport.h"
#include <windows.h>
#include <windowsx.h>

WindowSupport::WindowSupport(string titlePrm, HINSTANCE instancePrm, WNDPROC procFunPrm, HICON icon, int width, int height, int iCmdShow) :title(titlePrm), instance(instancePrm), procFun(procFunPrm), iCmdShow(iCmdShow) {
	GUID guid;
	CoCreateGuid(&guid);
	char buffer[64];
	sprintf_s(buffer, sizeof(buffer), "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}", guid.Data1, guid.Data2,
		guid.Data3, guid.Data4[0],
		guid.Data4[1], guid.Data4[2],
		guid.Data4[3], guid.Data4[4],
		guid.Data4[5], guid.Data4[6],
		guid.Data4[7]);
	className = string(buffer);
	tagWNDCLASSEXA wndRegist;
	wndRegist.cbSize = sizeof(tagWNDCLASSEXA);
	wndRegist.lpfnWndProc = procFun;
	wndRegist.cbClsExtra = 0;
	wndRegist.cbWndExtra = 0;
	wndRegist.hInstance = instance;
	wndRegist.hIcon = icon;
	wndRegist.hIconSm = icon;
	wndRegist.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndRegist.hbrBackground = GetStockBrush(WHITE_BRUSH);
	wndRegist.lpszMenuName = NULL;
	wndRegist.lpszClassName = buffer;
	wndRegist.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC | CS_DBLCLKS;
	if( !RegisterClassEx(&wndRegist) ) {
		throw wndRegist;
	}
	hwnd = CreateWindowEx(NULL, buffer, titlePrm.c_str(), WS_OVERLAPPEDWINDOW, 0, 0, width, height, NULL, NULL, instancePrm, NULL);
	if( !hwnd ) {
		throw hwnd;
	}
}

void WindowSupport::showWindow() {
	ShowWindow(hwnd, iCmdShow);
	while( GetMessage(&msg, NULL, 0, 0) ) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

WindowSupport::~WindowSupport() {
	try {

	} catch( exception  &e ) {
		;
	}
}
