#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

const char g_szClassName[] = "myWindowClass";


HWND hEdit;
char currentOperation = 0;
double firstNumber = 0.0;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
    {
      
        hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE | ES_RIGHT,
                               10, 10, 210, 25, hwnd, NULL, GetModuleHandle(NULL), NULL);
        
        CreateWindow("BUTTON", "+", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                     10, 50, 50, 50, hwnd, (HMENU)1, GetModuleHandle(NULL), NULL);
        
        CreateWindow("BUTTON", "-", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                     70, 50, 50, 50, hwnd, (HMENU)2, GetModuleHandle(NULL), NULL);
        
        CreateWindow("BUTTON", "*", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                     130, 50, 50, 50, hwnd, (HMENU)3, GetModuleHandle(NULL), NULL);
        
        CreateWindow("BUTTON", "/", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                     190, 50, 50, 50, hwnd, (HMENU)4, GetModuleHandle(NULL), NULL);
        
        CreateWindow("BUTTON", "=", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                     10, 110, 230, 50, hwnd, (HMENU)5, GetModuleHandle(NULL), NULL);
    }
    break;
    case WM_COMMAND:
    {
        if (LOWORD(wParam) >= 1 && LOWORD(wParam) <= 4)
        {
            char buffer[256];
            GetWindowText(hEdit, buffer, 256);
            firstNumber = atof(buffer);
            currentOperation = LOWORD(wParam);
            SetWindowText(hEdit, "");
        }
        else if (LOWORD(wParam) == 5)
        {
            char buffer[256];
            GetWindowText(hEdit, buffer, 256);
            double secondNumber = atof(buffer);
            double result = 0.0;

            switch (currentOperation)
            {
            case 1:
                result = firstNumber + secondNumber;
                break;
            case 2:
                result = firstNumber - secondNumber;
                break;
            case 3:
                result = firstNumber * secondNumber;
                break;
            case 4:
                if (secondNumber != 0.0)
                    result = firstNumber / secondNumber;
                else
                    MessageBox(hwnd, "Cannot divide by zero!", "Error", MB_OK | MB_ICONERROR);
                break;
            }

            snprintf(buffer, sizeof(buffer), "%f", result);
            SetWindowText(hEdit, buffer);
        }
    }
    break;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "Calculator",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 260, 200,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}
