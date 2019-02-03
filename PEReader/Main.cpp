#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include"WindowSupport.h"
#include <string>
#include "PEData.h"
using namespace std;

// 画面に表示される文字
string peDataStr;

LRESULT CALLBACK Winproc(HWND handle, UINT msg, WPARAM parm1, LPARAM parm2);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
	WindowSupport windowsupport(string("test"), hInstance, Winproc, LoadIcon(hInstance, reinterpret_cast<LPCSTR>(101)), 500, 500, iCmdShow);
	PEData pedata(string("d:\\software\\迅雷x\\program\\thunderstart.exe"));
	peDataStr = pedata.toString();
	windowsupport.showWindow();

	return 0;
}



LRESULT CALLBACK Winproc(HWND handle, UINT msg, WPARAM parm1, LPARAM parm2) {
	switch( msg ) {
	case WM_PAINT:
		PAINTSTRUCT ps;
		BeginPaint(handle, &ps);
		DrawText(ps.hdc, TEXT(peDataStr.c_str()), peDataStr.length(), &(ps.rcPaint), DT_LEFT);
		EndPaint(handle, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(handle, msg, parm1, parm2);
}
