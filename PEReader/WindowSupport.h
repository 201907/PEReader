#include <string>
#include <windows.h>
#include <windowsx.h>

using namespace std;

class WindowSupport {
public:
	WindowSupport(string titlePrm, HINSTANCE instancePrm, WNDPROC procFunPrm, HICON icon, int widthPrm, int heightPrm, int iCmdShow);
	~WindowSupport();
	void showWindow();
private:
	const string title;
	const HINSTANCE instance;
	const WNDPROC procFun;
	const int iCmdShow;
	string className;
	HWND hwnd;
	MSG msg;
};

