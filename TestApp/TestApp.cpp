// TestApp.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "TestApp.h"
#include "tchar.h"
#include <string>
#include <vector>
#include <cwctype>
#include <cmath>
#include <iostream>
#include <cctype> // Required for isdigit()

#define MAX_LOADSTRING      100
#define ID_INPUT_EDIT       1001
#define ID_OUTPUT_EDIT      1002
#define ID_PROCESS_BUTTON   1003
#define ID_DROPDOWN_COMBO   1004
#define ID_PROCESS_BUTTON2  1005
#define ID_BITWISE_EDIT     1006
#define ID_BITWISE_EDIT2    1007
#define ID_OUTPUT_EDIT2     1008

#define ID_PROCESS_BUTTON3  1009
#define ID_INPUT_EDIT2      1010
#define ID_OUTPUT_EDIT3     1011
// Define your enum
enum class OperationType {
    BITWISE_AND = 0,
    BITWISE_OR,
    BITWISE_XOR,
    SHIFTLEFT,
    SHIFTRIGHT
};

// Global Variables:
OperationType operationState;
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND hInputEdit, hOutputEdit, hProcessButton;
HWND hInputEdit2, hOutputEdit2, hProcessButton2;
HWND hInputEdit3;
HWND hDropdownCombo;

HWND hInputEdit4, hOutputEdit3, hProcessButton3;


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
std::wstring        ProcessUserInput(const std::wstring& input);
std::wstring        ProcessUserInputTwo(const std::wstring& input);
std::wstring        ProcessBitwiseInput(const std::wstring& input1, const std::wstring& input2, const OperationType& type);
OperationType       GetSelectedOperation();
std::wstring        OperationTypeToString(OperationType op);
int                 toInteger(std::wstring input);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.



    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TESTAPP, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTAPP));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TESTAPP));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TESTAPP);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   // Create input label
   CreateWindowW(L"STATIC", L"Decimal to Binary:", WS_VISIBLE | WS_CHILD,
       20, 20, 200, 20, hWnd, nullptr, hInstance, nullptr);

   // Create input text box
   hInputEdit = CreateWindowW(L"EDIT", L"",
       WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL,
       20, 45, 400, 20, hWnd, (HMENU)ID_INPUT_EDIT, hInstance, nullptr);

   // Create process button
   hProcessButton = CreateWindowW(L"BUTTON", L"Process",
       WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
       20, 70, 100, 30, hWnd, (HMENU)ID_PROCESS_BUTTON, hInstance, nullptr);

   // Create output label
   CreateWindowW(L"STATIC", L"Binary Output:", WS_VISIBLE | WS_CHILD,
       20, 105, 150, 20, hWnd, nullptr, hInstance, nullptr);

   // Create output text box (read-only)
   hOutputEdit = CreateWindowW(L"EDIT", L"",
       WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
       20, 130, 400, 20, hWnd, (HMENU)ID_OUTPUT_EDIT, hInstance, nullptr);


   // Create input label2
   CreateWindowW(L"STATIC", L"Binary to Decimal:", WS_VISIBLE | WS_CHILD,
       20, 155, 200, 20, hWnd, nullptr, hInstance, nullptr);

   // Create input text box
   hInputEdit4 = CreateWindowW(L"EDIT", L"",
       WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL,
       20, 180, 400, 20, hWnd, (HMENU)ID_INPUT_EDIT2, hInstance, nullptr);

   // Create process button
   hProcessButton3 = CreateWindowW(L"BUTTON", L"Process",
       WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
       20, 205, 100, 30, hWnd, (HMENU)ID_PROCESS_BUTTON3, hInstance, nullptr);

   // Create output label
   CreateWindowW(L"STATIC", L"Decimal Output:", WS_VISIBLE | WS_CHILD,
       20, 240, 150, 20, hWnd, nullptr, hInstance, nullptr);

   // Create output text box (read-only)
   hOutputEdit3 = CreateWindowW(L"EDIT", L"",
       WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
       20, 265, 400, 20, hWnd, (HMENU)ID_OUTPUT_EDIT3, hInstance, nullptr);




   // Create dropdown label
   CreateWindowW(L"STATIC", L"Operation:", WS_VISIBLE | WS_CHILD,
       500, 20, 100, 20, hWnd, nullptr, hInstance, nullptr);

   // Create dropdown ComboBox
   hDropdownCombo = CreateWindowW(L"COMBOBOX", L"",
       WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | CBS_HASSTRINGS,
       500, 45, 200, 200, hWnd, (HMENU)ID_DROPDOWN_COMBO, hInstance, nullptr);

   // Populate the dropdown with enum options
   SendMessageW(hDropdownCombo, CB_ADDSTRING, 0, (LPARAM)L"AND");
   SendMessageW(hDropdownCombo, CB_ADDSTRING, 0, (LPARAM)L"OR");
   SendMessageW(hDropdownCombo, CB_ADDSTRING, 0, (LPARAM)L"XOR");
   SendMessageW(hDropdownCombo, CB_ADDSTRING, 0, (LPARAM)L"Shift Left");
   SendMessageW(hDropdownCombo, CB_ADDSTRING, 0, (LPARAM)L"Shift Right");
   // Set default selection
   SendMessageW(hDropdownCombo, CB_SETCURSEL, 0, 0);


   //COMPARE

   CreateWindowW(L"STATIC", L"Input One:", WS_VISIBLE | WS_CHILD,
       500, 70, 100, 20, hWnd, nullptr, hInstance, nullptr);

   // Create input text box
   hInputEdit2 = CreateWindowW(L"EDIT", L"",
       WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL,
       500, 95, 400, 20, hWnd, (HMENU)ID_BITWISE_EDIT, hInstance, nullptr);

      // Create output label
   CreateWindowW(L"STATIC", L"Input Two:", WS_VISIBLE | WS_CHILD,
       500, 120, 100, 20, hWnd, nullptr, hInstance, nullptr);
   // Create input text box
   hInputEdit3 = CreateWindowW(L"EDIT", L"",
       WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL,
       500, 145, 400, 20, hWnd, (HMENU)ID_BITWISE_EDIT, hInstance, nullptr);
   // Create output text box (read-only)
   hOutputEdit2 = CreateWindowW(L"EDIT", L"",
       WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
       500, 205, 400, 20, hWnd, (HMENU)ID_BITWISE_EDIT2, hInstance, nullptr);
 
   //Create process button
   hProcessButton2 = CreateWindowW(L"BUTTON", L"Compare",
       WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
       500, 170, 100, 30, hWnd, (HMENU)ID_PROCESS_BUTTON2, hInstance, nullptr);


   
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        int wmEvent = HIWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case ID_DROPDOWN_COMBO:
            if (wmEvent == CBN_SELCHANGE)
            {
                // Handle dropdown selection change
                OperationType selectedOp = GetSelectedOperation();
                operationState = selectedOp;
                std::wstring statusText = L"Selected: " + OperationTypeToString(selectedOp);
                // You could display this in a status bar or debug output
                OutputDebugStringW(statusText.c_str());
            }
            break;
        case ID_PROCESS_BUTTON:
        {
            // Get text length from input box
            int inputLength = GetWindowTextLengthW(hInputEdit);
            if (inputLength > 0)
            {
                // Allocate buffer and get the text
                std::vector<wchar_t> buffer(inputLength + 1);
                GetWindowTextW(hInputEdit, buffer.data(), inputLength + 1);

                std::wstring inputText(buffer.data());

                // Process the input
                std::wstring outputText = ProcessUserInput(inputText);

                // Set the output text
                SetWindowTextW(hOutputEdit, outputText.c_str());
            }
            else
            {
                SetWindowTextW(hOutputEdit, L"Enter decimal value");
            }
        }
        break;
        case ID_PROCESS_BUTTON2:
        {
            // Get text length from input box 1
            int inputLength2 = GetWindowTextLengthW(hInputEdit2);
            int inputLength3 = GetWindowTextLengthW(hInputEdit3);
            if ((inputLength2 > 0 && inputLength3 > 0))
            {
                // Allocate buffer and get the text
                std::vector<wchar_t> buffer2(inputLength2 + 1);
                GetWindowTextW(hInputEdit2, buffer2.data(), inputLength2 + 1);

                std::wstring inputText2(buffer2.data());
                std::vector<wchar_t> buffer3(inputLength3 + 1);
                GetWindowTextW(hInputEdit3, buffer3.data(), inputLength3 + 1);

                std::wstring inputText3(buffer3.data());

                // Process the input
                std::wstring outputText = ProcessBitwiseInput(inputText2, inputText3, GetSelectedOperation());

                // Set the output text
                SetWindowTextW(hOutputEdit2, outputText.c_str());
            }
            else
            {
                SetWindowTextW(hOutputEdit2, L"Enter decimal value");
            }
            break;
        }
        case ID_PROCESS_BUTTON3:
        {
            // Get text length from input box
            int inputLength = GetWindowTextLengthW(hInputEdit4);
            if (inputLength > 0)
            {
                // Allocate buffer and get the text
                std::vector<wchar_t> buffer(inputLength + 1);
                GetWindowTextW(hInputEdit4, buffer.data(), inputLength + 1);

                std::wstring inputText(buffer.data());

                // Process the input
                std::wstring outputText = ProcessUserInputTwo(inputText);

                // Set the output text
                SetWindowTextW(hOutputEdit3, outputText.c_str());
            }
            else
            {
                SetWindowTextW(hOutputEdit3, L"Enter decimal value");
            }
        }
        break;
            break;
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
// Function to process the user input
std::wstring ProcessUserInput(const std::wstring& input)
{
    std::vector<int> binaryNum = {};
    // Example processing: convert to uppercase and add some text
    //std::wstring output = L"Processed: ";
    long long unsigned int outputNum = 0;
    int size = input.size() - 1;
    for (int c : input)
    {
        if (isdigit(c)) {
            outputNum += (c - L'0') * pow(10, size);
            size--;
        }
    }
    while (outputNum != 1) {
        binaryNum.push_back(outputNum % 2);
        outputNum = outputNum / 2;
    }
    binaryNum.push_back(1);
    //output += L"\n\nLength: " + std::to_wstring(input.length()) + L" characters";
    std::wstring output;
    for (int i = binaryNum.size() - 1; i >= 0; i--) {
        output += static_cast<char>(binaryNum[i] + L'0');
    }
    return output;
}
std::wstring ProcessUserInputTwo(const std::wstring& input)
{
    std::vector<int> binaryNum = {};
    // Example processing: convert to uppercase and add some text
    //std::wstring output = L"Processed: ";
    long long unsigned int outputNum = 0;
    int size = input.size() - 1;
    for (int c : input)
    {
        if (isdigit(c)) {
            outputNum += (c - L'0') * pow(2, size);
            size--;
        }
    }
    //output += L"\n\nLength: " + std::to_wstring(input.length()) + L" characters";
    std::wstring output = std::to_wstring(outputNum);
    return output;
}

std::wstring ProcessBitwiseInput(const std::wstring& input1, const std::wstring& input2, const OperationType& type)
{
    std::wstring finalString;
    int diff = input1.size() - input2.size();

    std::wstring diffFix;
    std::wstring base;
        int fix = toInteger(input2);
    
	
    for (int k = 0; k < abs(diff); k++) 
    {
        diffFix += L'0';
    }
    if (diff > 0) 
    {
        diffFix += input2;
        base = input1;
    }
    else 
    {
        diffFix += input1;
        base = input2;
    }

    switch (type)
    {
    case OperationType::BITWISE_AND:
        for (int i = 0; i < base.size(); i++)
        {
            if (base.at(i) == diffFix.at(i) && diffFix.at(i) != L'0')
            {
                finalString += '1';
            }
            else
            {
                finalString += '0';
            }
        }
        break;
    case OperationType::BITWISE_OR:
        for (int i = 0; i < base.size(); i++)
        {
            if (base.at(i) == L'1' || diffFix.at(i) == L'1')
            {
                finalString += '1';
            }
            else
            {
                finalString += '0';
            }
        }
        break;
    case OperationType::BITWISE_XOR:

        for (int j = 0; j < base.size(); j++)
        {
            if ((base.at(j) == L'1' && diffFix.at(j) != L'1') || (base.at(j) != L'1' && diffFix.at(j) == L'1'))
            {
                finalString += '1';
            }
            else
            {
                finalString += '0';
            }
        }
        break;

    case OperationType::SHIFTLEFT:
        finalString = input1;
        for (int i = 0; i < fix; i++) 
        {
            finalString += '0';
        }
        if (finalString.size() > 32) {
			finalString = finalString.substr(finalString.size() - 32, 32);
        }
        break;
    case OperationType::SHIFTRIGHT:
        for (int i = 0; i < fix; i++) {
            finalString += '0';
        }
        finalString += input1.substr(0, input1.size()-fix);
        break;
    }
    
    return finalString;
}
// Function to get the selected enum value from dropdown
OperationType GetSelectedOperation()
{
    int selectedIndex = SendMessageW(hDropdownCombo, CB_GETCURSEL, 0, 0);
    if (selectedIndex == CB_ERR)
        return OperationType::BITWISE_AND; // Default value

    return static_cast<OperationType>(selectedIndex);
}

// Function to convert enum to string (useful for debugging or display)
std::wstring OperationTypeToString(OperationType op)
{
    switch (op)
    {
    case OperationType::BITWISE_AND:   return L"Bitwise AND";
    case OperationType::BITWISE_OR:    return L"Bitwise OR";
    case OperationType::BITWISE_XOR:   return L"Bitwise XOR";
    default:                           return L"Unknown";
    }
}

int toInteger(std::wstring input)
{
    int outputNum = 0;
    for (int c : input)
    {
        if (isdigit(c)) {
            outputNum += (c - L'0');
        }
    }
    return outputNum;
}
