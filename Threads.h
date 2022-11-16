#pragma once
#include<windows.h>
#include<windowsx.h>
#include<tchar.h>
#include"resource.h"

class Threads
{
public:
	static Threads* ptr;
	Threads();
	static BOOL CALLBACK DlgProc(HWND hwnd, UINT message, WPARAM wp, LPARAM lp);
	BOOL Cls_OnInit(HWND hwnd, HWND hwndFocus, LPARAM lp);
	void Cls_onCommand(HWND hwnd, int is, HWND hwndCtrl, UINT codeNoyify);
	void Cls_OnClose(HWND hwnd);
	HANDLE hThreadTest, hThreadTimer;
	//INT nErrors = 4;
	HWND hCheckTimer, hEdit;
	HWND hRadioButtons[8];
};