#include"resource.h"
#include"Threads.h"

BOOL WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdline, int nCmdShow) {
	Threads obj;
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)Threads::DlgProc);
}