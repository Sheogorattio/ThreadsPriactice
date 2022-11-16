#include "Threads.h"
#include<ctime>

INT nErrors = 4;

Threads* Threads::ptr = NULL;

Threads::Threads() {
    ptr = this;
}

DWORD WINAPI ThreadTimer(LPVOID lp) {
    while (TRUE) {
        Threads::DlgProc(HWND(lp), WM_TIMER, 0, 0);
    }
    return 0;
}

BOOL Threads::Cls_OnInit(HWND hwnd, HWND hwndFocus, LPARAM lp)
{
    for (int i = 0; i < 8; i++) {
        hRadioButtons[i] = GetDlgItem(hwnd, IDC_RADIO1 + i);
    }
    hCheckTimer = GetDlgItem(hwnd, IDC_CHECK1);
    hEdit = GetDlgItem(hwnd, IDC_EDIT1);
    hThreadTimer = CreateThread(NULL, 0, ThreadTimer, hwnd, CREATE_SUSPENDED, NULL );
    return TRUE;
}



void Threads::Cls_onCommand(HWND hwnd, int id, HWND hwndCtrl, UINT codeNoyify)
{
    if (id == IDOK) {
        if (BST_CHECKED == SendMessage(hRadioButtons[0], BM_GETCHECK, 0, 0)) nErrors--;
        if (BST_CHECKED == SendMessage(hRadioButtons[2], BM_GETCHECK, 0, 0)) nErrors--;
        if (BST_CHECKED == SendMessage(hRadioButtons[5], BM_GETCHECK, 0, 0)) nErrors--;
        if (BST_CHECKED == SendMessage(hRadioButtons[7], BM_GETCHECK, 0, 0)) nErrors--;
        TCHAR res[100];
        _stprintf_s(res, TEXT("your rezult is %d points"), 4 - nErrors);
        MessageBox(hwnd, res, TEXT("rezult"), MB_ICONINFORMATION | MB_OK);
        nErrors = 4;
    }
    if (id == IDCANCEL) {
        EndDialog(hwnd, 0);
    }
    if (id == IDC_CHECK1) {
        if (BST_CHECKED == SendMessage(hCheckTimer, BM_GETCHECK, 0, 0)) {
            ResumeThread(hThreadTimer);
            return;
        }
        SuspendThread(hThreadTimer);
    }
}

void Threads::Cls_OnClose(HWND hwnd) {
    KillTimer(hwnd, 1);
    EndDialog(hwnd, 0);
}

BOOL CALLBACK Threads::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInit);
        HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_onCommand);
        HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
    case WM_TIMER:
        LONGLONG t = time(NULL);
        TCHAR str[255];
        lstrcpy(str, _tctime(&t));
        str[lstrlen(str) - 1] = '\0';
        SetWindowText(ptr->hEdit, str);
    }
    return 0;
}
