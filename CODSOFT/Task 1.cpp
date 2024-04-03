#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <sstream>

HWND guessEdit, guessButton;
int randomNumber;

void generateRandomNumber() {
    srand(static_cast<unsigned int>(time(nullptr)));
    randomNumber = rand() % 100 + 1;
}

void showMessage(HWND hwnd, const wchar_t* message) {
    MessageBoxW(hwnd, message, L"Number Guessing Game", MB_OK | MB_ICONINFORMATION);
}

void onGuessButtonClick(HWND hwnd) {
    wchar_t guessText[10];
    GetWindowTextW(guessEdit, guessText, 10);
    int guess = _wtoi(guessText);

    if (guess == randomNumber) {
        showMessage(hwnd, L"Congratulations! You guessed it right!");
    }
    else if (guess < randomNumber) {
        showMessage(hwnd, L"Incorrect! Too low!");
    }
    else {
        showMessage(hwnd, L"Incorrect! Too high!");
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        guessEdit = CreateWindowW(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
            100, 50, 50, 20, hwnd, NULL, NULL, NULL);

        guessButton = CreateWindowW(L"BUTTON", L"Guess", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
            160, 50, 50, 20, hwnd, NULL, NULL, NULL);
        break;

    case WM_COMMAND:
        if (lParam == (LPARAM)guessButton) {
            onGuessButtonClick(hwnd);
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
    generateRandomNumber();

    WNDCLASSW wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"NumberGuessingGame";
    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(0, L"NumberGuessingGame", L"Number Guessing Game", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 300, 150, NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {};
    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return 0;
}
