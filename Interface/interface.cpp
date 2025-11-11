#include "Interface.h"
#include "..\Cryptage\chiffrement.h"
#include "..\DATAhandler\data_write.h"
InterfaceApp::InterfaceApp(HINSTANCE hInst) : hInstance(hInst), hwnd(NULL) {}

void InterfaceApp::createControls(HWND hwnd) {
    RECT rect; GetClientRect(hwnd, &rect);
    int width = rect.right, centerX = width / 2;

    CreateWindowW(L"STATIC", L"🛡️ Encryption Tool", WS_VISIBLE | WS_CHILD | SS_CENTER,
        0, 20, width, 25, hwnd, NULL, hInstance, NULL);

    hStatus = CreateWindowW(L"STATIC", filePath.c_str(), WS_VISIBLE | WS_CHILD | SS_CENTER,
        0, 50, width, 20, hwnd, NULL, hInstance, NULL);

    hFileBox = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
        centerX - 150, 80, 250, 25, hwnd, NULL, hInstance, NULL);

    hBrowseBtn = CreateWindowW(L"BUTTON", L"Browse...", WS_VISIBLE | WS_CHILD,
        centerX + 110, 80, 80, 25, hwnd, (HMENU)ID_BUTTON_BROWSE, hInstance, NULL);

    hChiffreBtn = CreateWindowW(L"BUTTON", L"Chiffrement", WS_VISIBLE | WS_CHILD,
        centerX - 150, 120, 100, 30, hwnd, (HMENU)ID_BUTTON_CHIFFRER, hInstance, NULL);

    hDechiffreBtn = CreateWindowW(L"BUTTON", L"Déchiffrement", WS_VISIBLE | WS_CHILD,
        centerX - 40, 120, 100, 30, hwnd, (HMENU)ID_BUTTON_DECHIFFRER, hInstance, NULL);

    hCombo = CreateWindowW(L"COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE,
        centerX + 80, 120, 150, 100, hwnd, (HMENU)ID_COMBO_SECURITY, hInstance, NULL);

    SendMessageW(hCombo, CB_ADDSTRING, 0, (LPARAM)L"Security LVL1");
    SendMessageW(hCombo, CB_ADDSTRING, 0, (LPARAM)L"Security LVL2");
    SendMessageW(hCombo, CB_ADDSTRING, 0, (LPARAM)L"Security LVL3");
    SendMessageW(hCombo, CB_SETCURSEL, 0, 0);
}

LRESULT CALLBACK InterfaceApp::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    InterfaceApp* app;
    if (msg == WM_NCCREATE) {
        app = static_cast<InterfaceApp*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)app);
        app->hwnd = hwnd;
    } else {
        app = reinterpret_cast<InterfaceApp*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }
    return app ? app->handleMessage(hwnd, msg, wParam, lParam)
               : DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT InterfaceApp::handleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        createControls(hwnd);
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
       case ID_BUTTON_BROWSE: {
    OPENFILENAMEW ofn{};
    WCHAR szFile[260] = {0};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"Text Files\0*.txt\0All Files\0*.*\0";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    
    if (GetOpenFileNameW(&ofn)) {
        std::wstring selectedPath = szFile;

        // Check if the extension is .txt (case-insensitive)
        if (selectedPath.length() >= 4 &&
            (_wcsicmp(selectedPath.substr(selectedPath.length() - 4).c_str(), L".txt") == 0)) {
            
            filePath = selectedPath;
            SetWindowTextW(hFileBox, selectedPath.c_str());
            SetWindowTextW(hStatus, L"File selected successfully!");
        } else {
            SetWindowTextW(hStatus, L"Error: Please select a .txt file!");
        }
    }
    break;
}

        case ID_BUTTON_CHIFFRER: {
    SetWindowTextW(hStatus, L"Chiffrement in progress...");

    if (!filePath.empty()) {
        // Convert wide string path to std::string
        int size_needed = WideCharToMultiByte(CP_UTF8, 0, filePath.c_str(), -1, NULL, 0, NULL, NULL);
        std::string filePathStr(size_needed, 0);
        WideCharToMultiByte(CP_UTF8, 0, filePath.c_str(), -1, &filePathStr[0], size_needed, NULL, NULL);

        // Read the text file
        data_write dw(filePathStr);
        std::string text = dw.read();

        // Get the selected security level from combo box
        int mode = SendMessageW(hCombo, CB_GETCURSEL, 0, 0) + 1; // 1,2,3

        // Encrypt the text
        Chiffrement c;
        std::string encryptedText = c.process(text, mode, true);

        // Write back to file
        dw.write(encryptedText);

        SetWindowTextW(hStatus, L"File encrypted successfully!");
    }
    break;
}

case ID_BUTTON_DECHIFFRER: {
    SetWindowTextW(hStatus, L"Déchiffrement in progress...");

    if (!filePath.empty()) {
        // Convert wide string path to std::string
        int size_needed = WideCharToMultiByte(CP_UTF8, 0, filePath.c_str(), -1, NULL, 0, NULL, NULL);
        std::string filePathStr(size_needed, 0);
        WideCharToMultiByte(CP_UTF8, 0, filePath.c_str(), -1, &filePathStr[0], size_needed, NULL, NULL);

        // Read the text file
        data_write dw(filePathStr);
        std::string text = dw.read();

        // Get the selected security level from combo box
        int mode = SendMessageW(hCombo, CB_GETCURSEL, 0, 0) + 1; // 1,2,3

        // Decrypt the text
        Chiffrement c;
        std::string decryptedText = c.process(text, mode, false);

        // Write back to file
        dw.write(decryptedText);

        SetWindowTextW(hStatus, L"File decrypted successfully!");
    }
    break;
}

        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int InterfaceApp::run(int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"EncryptionGUIClass";
    WNDCLASSW wc{};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClassW(&wc);

    hwnd = CreateWindowExW(0, CLASS_NAME, L"Encryption GUI",
    WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, // fixed-size
    CW_USEDEFAULT, CW_USEDEFAULT, 600, 250,
    NULL, NULL, hInstance, this);


    ShowWindow(hwnd, nCmdShow);

    MSG msg{};
    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return (int)msg.wParam;
}

