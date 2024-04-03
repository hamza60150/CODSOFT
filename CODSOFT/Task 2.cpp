#include <windows.h>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

HWND number1Edit, number2Edit, resultEdit;
HWND addButton, subtractButton, multiplyButton, divideButton;

void performOperation(int operation) {
    wchar_t number1Text[10], number2Text[10];
    GetWindowTextW(number1Edit, number1Text, 10);
    GetWindowTextW(number2Edit, number2Text, 10);

    double number1 = _wtof(number1Text);
    double number2 = _wtof(number2Text);
    double result = 0.0;

    switch (operation) {
    case 1: // Addition
        result = number1 + number2;
        break;
    case 2: // Subtraction
        result = number1 - number2;
        break;
    case 3: // Multiplication
        result = number1 * number2;
        break;
    case 4: // Division
        if (number2 != 0) {
            result = number1 / number2;
        }
        else {
            MessageBoxW(NULL, L"Cannot divide by zero!", L"Error", MB_OK | MB_ICONERROR);
            return;
        }
        break;
    default:
        return;
    }

    wstringstream ss;
    ss << fixed << setprecision(10) << result; // Set precision to 10 decimal places
    wstring resultString = ss.str();
    resultString.erase(resultString.find_last_not_of(L'0') + 1, wstring::npos); // Remove trailing zeros
    if (resultString.back() == L'.') resultString.pop_back(); // Remove trailing decimal point if it's the last character

    SetWindowTextW(resultEdit, resultString.c_str());
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        number1Edit = CreateWindowW(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER,
            20, 20, 100, 30, hwnd, NULL, NULL, NULL);

        number2Edit = CreateWindowW(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER,
            140, 20, 100, 30, hwnd, NULL, NULL, NULL);

        resultEdit = CreateWindowW(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_READONLY,
            260, 20, 100, 30, hwnd, NULL, NULL, NULL);

        addButton = CreateWindowW(L"BUTTON", L"Add", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
            20, 70, 80, 30, hwnd, (HMENU)1, NULL, NULL);

        subtractButton = CreateWindowW(L"BUTTON", L"Subtract", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
            120, 70, 80, 30, hwnd, (HMENU)2, NULL, NULL);

        multiplyButton = CreateWindowW(L"BUTTON", L"Multiply", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
            220, 70, 80, 30, hwnd, (HMENU)3, NULL, NULL);

        divideButton = CreateWindowW(L"BUTTON", L"Divide", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
            320, 70, 80, 30, hwnd, (HMENU)4, NULL, NULL);
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 1: // Add button clicked
            performOperation(1);
            break;
        case 2: // Subtract button clicked
            performOperation(2);
            break;
        case 3: // Multiply button clicked
            performOperation(3);
            break;
        case 4: // Divide button clicked
            performOperation(4);
            break;
        default:
            break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProcW(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSW wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"Calculator";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);

    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(0, L"Calculator", L"Calculator", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 430, 150, NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {};
    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return 0;
}
