#pragma once
#define UNICODE
#define _UNICODE
#include <windows.h>
#include <commdlg.h>
#include <string>


#define ID_BUTTON_CHIFFRER   1
#define ID_BUTTON_DECHIFFRER 2
#define ID_BUTTON_BROWSE     3
#define ID_COMBO_SECURITY    4

class InterfaceApp {
    HINSTANCE hInstance;
    HWND hwnd, hStatus, hFileBox, hBrowseBtn, hChiffreBtn, hDechiffreBtn, hCombo;
    std::wstring filePath = L"No file selected.";

public:
    InterfaceApp(HINSTANCE hInst);
    int run(int nCmdShow);

private:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT handleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    void createControls(HWND hwnd);
};
