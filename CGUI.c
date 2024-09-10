#include <windows.h>

// Global Variables
LPCSTR szClassName = "BasicWindowClass";  // Window Class Name
HWND hEdit, hButton, hListBox;            // Handles for the Edit control, Button, and ListBox

// Window Procedure function declaration
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// WinMain: The entry point for any Windows Desktop Application
int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow
) {
    WNDCLASS wc = { 0 };  // Window Class Structure
    HWND hwnd;            // Handle to the window
    MSG msg;              // Message structure

    // 1. Define the Window Class
    wc.lpfnWndProc = WndProc;          // Window Procedure function
    wc.hInstance = hInstance;          // Application handle
    wc.lpszClassName = szClassName;    // Class name
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1); // Window background color
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);    // Default arrow cursor
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);  // Default application icon

    // 2. Register the Window Class
    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // 3. Create the Window
    hwnd = CreateWindow(
        szClassName,             // Window class name
        "To-Do List Application", // Window title
        WS_OVERLAPPEDWINDOW,     // Window style
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 400,  // Position and size
        NULL, NULL, hInstance, NULL              // Parent, Menu, App instance, Additional data
    );

    if (hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // 4. Display the window
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // 5. The Message Loop
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

// Window Procedure: Processes messages for the window
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            // Create Edit Control for input
            hEdit = CreateWindow(
                "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                20, 20, 300, 25, hwnd, NULL, NULL, NULL
            );

            // Create Button to add task
            hButton = CreateWindow(
                "BUTTON", "Add Task", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                330, 20, 100, 25, hwnd, (HMENU) 1, NULL, NULL
            );

            // Create ListBox to display tasks
            hListBox = CreateWindow(
                "LISTBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LBS_NOTIFY,
                20, 60, 410, 200, hwnd, NULL, NULL, NULL
            );
            break;

        case WM_COMMAND:
            if (LOWORD(wParam) == 1) {
                // Handle Add Task button click
                char task[256]; // Buffer to store the entered task
                GetWindowText(hEdit, task, sizeof(task)); // Get the text from the Edit control

                if (strlen(task) > 0) {
                    // Add the task to the ListBox
                    SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)task);

                    // Clear the Edit control after adding the task
                    SetWindowText(hEdit, "");
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
