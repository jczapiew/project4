// draw.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "draw.h"

#define MAX_LOADSTRING 100
#define TMR_1 1

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

												//INT value;
int currentFloor = 1;
bool up = true;

HWND hwndButton;
RECT drawArea = { 552, 2, 848, 601 };

std::vector<int> vector1;
std::vector<int> vector2;
std::vector<int> vector3;
std::vector<int> vector4;
std::vector<int> vector5;
std::vector<int> liftingVector;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


void MyOnPaint(HDC hdc)
{
	//value++;
	Graphics graphics(hdc);
	Pen pen(Color(255, 0, 200, 13), 2);
	graphics.DrawLine(&pen, 10, 120, 550, 120);
	graphics.DrawLine(&pen, 850, 240, 1390, 240);
	graphics.DrawLine(&pen, 10, 360, 550, 360);
	graphics.DrawLine(&pen, 850, 480, 1390, 480);
	graphics.DrawLine(&pen, 10, 600, 550, 600);
	Pen pen2(Color(255, 10, 50, 10), 3);
	graphics.DrawLine(&pen2, 550, 0, 550, 603);
	graphics.DrawLine(&pen2, 550, 0, 850, 0);
	graphics.DrawLine(&pen2, 850, 0, 850, 603);
	graphics.DrawLine(&pen2, 550, 603, 850, 603);
	Pen lift(Color(255, 235, 205, 10), 3);
	graphics.DrawLine(&lift, 560, 600, 840, 600);
	graphics.DrawLine(&lift, 560, 500, 840, 500);
	graphics.DrawLine(&lift, 560, 500, 560, 600);
	graphics.DrawLine(&lift, 840, 500, 840, 600);
}

void poppingVector(std::vector<int> &current, int indeks)
{
	std::vector<int> temporary;
	temporary.clear();
	int lolSize = current.size();
	int julek = 0;
	for (int i = 0; i < lolSize; i++) {
		if (i == indeks) {
			i--;
			julek++;
			lolSize--;
			indeks = -1;
			continue;
		}
		temporary.push_back(current[julek]);
		julek++;
	}
	current.clear();
	for (int i = 0; i < temporary.size(); i++) {
		current.push_back(temporary[i]);
	}
}

void repaintLift(HWND hWnd, HDC &hdc, PAINTSTRUCT &ps, RECT *drawArea)
{
	InvalidateRect(hWnd, drawArea, TRUE);
	hdc = BeginPaint(hWnd, &ps);
	Graphics graphics(hdc);
	switch (currentFloor)
	{
	case 1: {
		while (vector1.size()) {
			if (liftingVector.size() == 8) break;
			liftingVector.push_back(vector1[0]);
			poppingVector(vector1, 0);
		}
		if (liftingVector.empty()) {
			if (!vector2.empty()) {
				if (vector2[0] == 1) up = false;
				else up = true;
				currentFloor = 2;
			}
			else if (!vector3.empty()) {
				if (vector3[0] < 3) up = false;
				else up = true;
				currentFloor = 3;
			}
			else if (!vector4.empty()) {
				if (vector4[0] == 5) up = true;
				else up = false;
				currentFloor = 4;
			}
			else if (!vector5.empty()) {
				currentFloor = 5;
			}
		}
		break;
	}
	case 2: {
		for (int i = 0; i < vector2.size(); i++) {
			if (liftingVector.size() == 8) break;
			if (up && (vector2[0] > 2)) {
				liftingVector.push_back(vector2[i]);
				poppingVector(vector2, i);
				i--;
			}
			else if (!up && (vector2[0] < 2)) {
				liftingVector.push_back(vector2[i]);
				poppingVector(vector2, i);
				i--;
			}
		}
		if (liftingVector.empty()) {
			if (up) {
				if (!vector3.empty()) {
					currentFloor = 3;
					break;
				}
				else if (!vector4.empty()) {
					currentFloor = 4;
					break;
				}
				else if (!vector5.empty()) {
					currentFloor = 5;
					break;
				}
				else if (!vector2.empty()) {
					up = false;
					break;
				}
				else if (!vector1.empty()) {
					currentFloor = 1;
					break;
				}
			}
			else if (!up) {
				if (!vector1.empty()) {
					currentFloor = 1;
					break;
				}
				else if (!vector2.empty()) {
					up = true;
					break;
				}
				else if (!vector3.empty()) {
					up = true;
					currentFloor = 3;
					break;
				}
				else if (!vector4.empty()) {
					up = true;
					currentFloor = 4;
					break;
				}
				else if (!vector5.empty()) {
					up = true;
					currentFloor = 5;
					break;
				}
			}
		}
		break;
	}
	case 3: {
		for (int i = 0; i < vector3.size(); i++) {
			if (liftingVector.size() == 8) break;
			if (up && (vector3[i] > 3)) {
				liftingVector.push_back(vector3[i]);
				poppingVector(vector3, i);
				i--;
			}
			else if (!up && (vector3[i] < 3)) {
				liftingVector.push_back(vector3[i]);
				poppingVector(vector3, i);
				i--;
			}
		}
		if (liftingVector.empty()) {
			if (up) {
				if (!vector4.empty()) {
					currentFloor = 4;
					break;
				}
				else if (!vector5.empty()) {
					currentFloor = 5;
					break;
				}
				else if (!vector3.empty()) {
					up = false;
					break;
				}
				else if (!vector2.empty()) {
					up = false;
					currentFloor = 2;
					break;
				}
				else if (!vector1.empty()) {
					currentFloor = 1;
					break;
				}
			}
			else if (!up) {
				if (!vector2.empty()) {
					currentFloor = 2;
					break;
				}
				else if (!vector1.empty()) {
					currentFloor = 1;
					break;
				}
				else if (!vector3.empty()) {
					up = true;
					break;
				}
				else if (!vector4.empty()) {
					up = true;
					currentFloor = 4;
					break;
				}
				else if (!vector5.empty()) {
					up = true;
					currentFloor = 5;
					break;
				}
			}
		}
		break;
	}
	case 4: {
		for (int i = 0; i < vector4.size(); i++) {
			if (liftingVector.size() == 8) break;
			if (up && (vector4[i] > 4)) {
				liftingVector.push_back(vector4[i]);
				poppingVector(vector4, i);
				i--;
			}
			else if (!up && (vector4[i] < 4)) {
				liftingVector.push_back(vector4[i]);
				poppingVector(vector4, i);
				i--;
			}
		}
		if (liftingVector.empty()) {
			if (up) {
				if (!vector5.empty()) {
					currentFloor = 5;
					break;
				}
				else if (!vector4.empty()) {
					up = false;
					break;
				}
				else if (!vector3.empty()) {
					up = false;
					currentFloor = 3;
					break;
				}
				else if (!vector2.empty()) {
					up = false;
					currentFloor = 2;
					break;
				}
				else if (!vector5.empty()) {
					currentFloor = 1;
					break;
				}
			}
			else if (!up) {
				if (!vector3.empty()) {
					currentFloor = 3;
					break;
				}
				else if (!vector2.empty()) {
					currentFloor = 2;
					break;
				}
				else if (!vector1.empty()) {
					currentFloor = 1;
					break;
				}
				else if (!vector4.empty()) {
					up = true;
					break;
				}
				else if (!vector5.empty()) {
					currentFloor = 5;
					break;
				}
			}
		}
		break;
	}
	case 5: {
		while (vector5.size()) {
			if (liftingVector.size() == 8) break;
			liftingVector.push_back(vector5[0]);
			poppingVector(vector5, 0);
		}
		if (liftingVector.empty()) {
			if (!vector4.empty()) {
				if (vector4[0] == 5) up = true;
				else up = false;
				currentFloor = 4;
			}
			else if (!vector3.empty()) {
				if (vector3[0] < 3) up = false;
				else up = true;
				currentFloor = 3;
			}
			else if (!vector2.empty()) {
				if (vector2[0] == 1) up = false;
				else up = true;
				currentFloor = 2;
			}
			else if (!vector1.empty()) {
				currentFloor = 1;
			}
		}
		break;
	}
	default: break;
	}
	Pen lift(Color(255, 235, 205, 10), 3);
	graphics.DrawLine(&lift, 560, (720 - (currentFloor * 120)), 840, (720 - (currentFloor * 120)));
	graphics.DrawLine(&lift, 560, (620 - (currentFloor * 120)), 840, (620 - (currentFloor * 120)));
	graphics.DrawLine(&lift, 560, (620 - (currentFloor * 120)), 560, (720 - (currentFloor * 120)));
	graphics.DrawLine(&lift, 840, (620 - (currentFloor * 120)), 840, (720 - (currentFloor * 120)));
	if (!liftingVector.empty()) {
		if (liftingVector[0] < currentFloor) up = false;
		if (liftingVector[0] > currentFloor) up = true;
		currentFloor = liftingVector[0];
	}
	for (int i = 0; i < liftingVector.size(); i++) {
		if (up && (liftingVector[i] > currentFloor) && (liftingVector[i] < liftingVector[0])) {
			currentFloor = liftingVector[i];
			i = 0;
		}
		else if (!up && (liftingVector[i] < currentFloor) && (liftingVector[i] > liftingVector[0])) {
			currentFloor = liftingVector[i];
			i = 0;
		}
	}
	for (int i = 0; i < liftingVector.size(); i++) {
		if (liftingVector[i] == currentFloor) {
			switch (currentFloor)
			{
			case 1:
			{
				poppingVector(liftingVector, i);
				i--;
				break;
			}
			case 2:
			{
				poppingVector(liftingVector, i);
				i--;
				break;
			}
			case 3:
			{
				poppingVector(liftingVector, i);
				i--;
				break;
			}
			case 4:
			{
				poppingVector(liftingVector, i);
				i--;
				break;
			}
			case 5:
			{
				poppingVector(liftingVector, i);
				i--;
				break;
			}
			default: break;
			}
		}
	}
	EndPaint(hWnd, &ps);
}

int OnCreate(HWND window)
{
	SetTimer(window, TMR_1, 25, 0);
	return 0;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	//value = 10;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAW));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAW));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_DRAW);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
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
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("1"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 5,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON51,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("2"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 28,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON52,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("3"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 51,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON53,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("4"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 74,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON54,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("1"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1370, 125,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON41,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("2"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1370, 148,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON42,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("3"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1370, 171,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON43,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("5"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1370, 217,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON45,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("1"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 245,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON31,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("2"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 268,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON32,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("4"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 314,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON34,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("5"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 337,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON35,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("1"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1370, 365,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON21,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("3"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1370, 411,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON23,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("4"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1370, 434,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON24,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("5"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1370, 457,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON25,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("2"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 508,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON12,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("3"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 531,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON13,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("4"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 554,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON14,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("5"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 577,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON15,
		hInstance,
		NULL);

	OnCreate(hWnd);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	//OnCreate(hWnd,wParam,lParam);
	//OnTimer(hWnd,wParam,lParam);

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case ID_BUTTON51:
		{
			vector5.push_back(1);
			break;
		}
		case ID_BUTTON52:
		{
			vector5.push_back(2);
			break;
		}
		case ID_BUTTON53:
		{
			vector5.push_back(3);
			break;
		}
		case ID_BUTTON54:
		{
			vector5.push_back(4);
			break;
		}
		case ID_BUTTON41:
		{
			vector4.push_back(1);
			break;
		}
		case ID_BUTTON42:
		{
			vector4.push_back(2);
			break;
		}
		case ID_BUTTON43:
		{
			vector4.push_back(3);
			break;
		}
		case ID_BUTTON45:
		{
			vector4.push_back(5);
			break;
		}
		case ID_BUTTON31:
		{
			vector3.push_back(1);
			break;
		}
		case ID_BUTTON32:
		{
			vector3.push_back(2);
			break;
		}
		case ID_BUTTON34:
		{
			vector3.push_back(4);
			break;
		}
		case ID_BUTTON35:
		{
			vector3.push_back(5);
			break;
		}
		case ID_BUTTON21:
		{
			vector2.push_back(1);
			break;
		}
		case ID_BUTTON23:
		{
			vector2.push_back(3);
			break;
		}
		case ID_BUTTON24:
		{
			vector2.push_back(4);
			break;
		}
		case ID_BUTTON25:
		{
			vector2.push_back(5);
			break;
		}
		case ID_BUTTON12:
		{
			vector1.push_back(2);
			break;
		}
		case ID_BUTTON13:
		{
			vector1.push_back(3);
			break;
		}
		case ID_BUTTON14:
		{
			vector1.push_back(4);
			break;
		}
		case ID_BUTTON15:
		{
			vector1.push_back(5);
			break;
		}
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		MyOnPaint(hdc);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_TIMER:
		switch (wParam)
		{
		case TMR_1:
			//force window to repaint
			hdc = BeginPaint(hWnd, &ps);
			repaintLift(hWnd, hdc, ps, &drawArea);
			EndPaint(hWnd, &ps);
			Sleep(200);
			break;
		}

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