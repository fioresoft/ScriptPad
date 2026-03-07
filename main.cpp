#include <windows.h>
#include <atlapp.h>
#include <atlbase.h>
#include <atlwin.h>
#include "EditorWnd.h"

CAppModule _Module;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int) {
    _Module.Init(NULL, hInst);

    CMessageLoop loop;
    _Module.AddMessageLoop(&loop);

    EditorWindow wnd;
    wnd.Create(NULL, CWindow::rcDefault, L"VBScript Editor (C++ + Scintilla 5.x)");
    wnd.ShowWindow(SW_SHOW);

    int ret = loop.Run();
    _Module.RemoveMessageLoop();
    _Module.Term();
    return ret;
}
