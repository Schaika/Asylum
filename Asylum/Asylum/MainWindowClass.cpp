#include "MainWindowClass.h"
#include "Menuing.h"
#include <Windowsx.h>
MainWindowClass::MainWindowClass(HINSTANCE p_hInstance,  WNDPROC p_WindowProcedure, LPCUWSTR p_windowName, int p_width, int p_height) : hPrevInstance(p_hInstance)
{
	
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hInstance = p_hInstance;
	windowClass.lpszClassName = L"CommonWindow";
	windowClass.lpfnWndProc = p_WindowProcedure;

	RECT rect = { 0 };
	GetClientRect(GetDesktopWindow(), &rect);
	rect.left = (rect.right / 2) - (p_width / 2);
	rect.top = (rect.bottom / 2) - (p_height / 2);

	if (!RegisterClassW(&windowClass)) {
		MessageBox(NULL, L"Hello nigger! You failed lol!", L"HornyPonyBLM", MB_OK);
	}
	windowHWND = CreateWindowW(windowClass.lpszClassName, p_windowName, WS_OVERLAPPED | WS_VISIBLE | WS_MINIMIZEBOX | WS_SYSMENU, rect.left, rect.top, p_width, p_height, NULL, NULL, NULL, NULL);
	initMenu();
	initControls();
}

MainWindowClass::~MainWindowClass()
{
}

void MainWindowClass::handleMenu(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{

}

void MainWindowClass::initMenu()
{
	HMENU mainMenu = CreateMenu();
	HMENU fileMenu = CreateMenu();
	HMENU fileSubMenu = CreateMenu();
	HMENU helpMenu = CreateMenu();

	AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)fileMenu, L"File");
	AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)helpMenu, L"Help");

	AppendMenu(fileMenu, MF_STRING, MENU_OPEN, L"Open");
	AppendMenu(fileMenu, MF_POPUP, (UINT_PTR)fileSubMenu, L"Save as...");
	AppendMenu(fileMenu, MF_STRING, MENU_OPENLINK, L"Open Funny Video");
	AppendMenu(fileMenu, MF_STRING, MENU_CHANGETITLE, L"Change Window Title");
	AppendMenu(fileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(fileMenu, MF_STRING, MENU_EXIT, L"Exit");

	AppendMenu(fileSubMenu, MF_STRING, NULL, L".txt");
	AppendMenu(fileSubMenu, MF_STRING, NULL, L".bin");

	AppendMenu(helpMenu, MF_STRING, MENU_ABOUT, L"About");
	SetMenu(windowHWND, mainMenu);
}

void MainWindowClass::initControls()
{
	RECT rect = { 0 };
	GetClientRect(windowHWND, &rect);
	{
		const int resizeConst = 100;
		int x1 = 0;
		int w1 = rect.right / 2 - resizeConst / 2;
		int x2 = w1 + x1;
		int w2 = resizeConst;
		int x3 = x2 + w2;
		{
			LOGFONT logfont = { 0 };
			logfont.lfCharSet = DEFAULT_CHARSET;
			logfont.lfHeight = -22;
			HFONT hFont = CreateFontIndirect(&logfont);

			auto tmp = CreateWindowW(L"Static", L"Undead", WS_VISIBLE | WS_CHILD | SS_CENTER, x2, 3, w2, 20, windowHWND, NULL, hPrevInstance, NULL);
			SendMessage(tmp, WM_SETFONT, (WPARAM)hFont, TRUE);
		}
		{
			LOGFONT logfont = { 0 };
			logfont.lfCharSet = DEFAULT_CHARSET;
			logfont.lfHeight = -16;
			HFONT hFont = CreateFontIndirect(&logfont);

			auto tmp1 = CreateWindowW(L"Static", L"Northern", WS_VISIBLE | WS_CHILD | SS_RIGHT, x1, 3, w1, 20, windowHWND, NULL, hPrevInstance, NULL);
			auto tmp2 = CreateWindowW(L"Static", L"Asylum", WS_VISIBLE | WS_CHILD | SS_LEFT, x3, 3, rect.right / 3, 20, windowHWND, NULL, hPrevInstance, NULL);
			SendMessage(tmp1, WM_SETFONT, (WPARAM)hFont, TRUE);
			SendMessage(tmp2, WM_SETFONT, (WPARAM)hFont, TRUE);
		}
	}
	hListBox = CreateWindowW(L"LISTBOX", NULL, WS_VISIBLE | WS_CHILD | LBS_SORT | LBS_STANDARD| WS_VSCROLL | LBS_DISABLENOSCROLL, 5, 25, 200, 400, windowHWND, (HMENU)LISTBOX_ITEM, hPrevInstance, NULL);
	
	{
		unsigned int x = 215;
		unsigned int y = 25;
		//сколько очков у больного
		CreateWindowW(L"Static", L"Score: ", WS_VISIBLE | WS_CHILD | SS_RIGHT, x, y, 50, 20, windowHWND, NULL, hPrevInstance, NULL);
		x += 50;
		hScore = CreateWindowW(L"Static", L"0", WS_VISIBLE | WS_CHILD | SS_LEFT, x, y, 35, 20, windowHWND, NULL, hPrevInstance, NULL);
		x += 35;

		//дни
		CreateWindowW(L"Static", L"Day: ", WS_VISIBLE | WS_CHILD | SS_RIGHT, x, y, 50, 20, windowHWND, NULL, hPrevInstance, NULL);
		x += 50;
		hDays = CreateWindowW(L"Static", L"1", WS_VISIBLE | WS_CHILD | SS_LEFT, x, y, 45, 20, windowHWND, NULL, hPrevInstance, NULL);
		x += 45;

		//вместимость
		CreateWindowW(L"Static", L"Capacity: ", WS_VISIBLE | WS_CHILD | SS_RIGHT, x, y, 80, 20, windowHWND, NULL, hPrevInstance, NULL);
		x += 80;
		hCapacity = CreateWindowW(L"Static", L"1/25", WS_VISIBLE | WS_CHILD | SS_LEFT, x, y, 35, 20, windowHWND, NULL, hPrevInstance, NULL);
		x += 35;

	}


	hNextDayButton = CreateWindowW(L"Button", L"Next day", WS_VISIBLE | WS_CHILD, 215, 50, 75, 35, windowHWND, (HMENU)BUTTON_NEXTDAY, hPrevInstance, NULL);
	hWholePeriodButton = CreateWindowW(L"Button", L"Simulate", WS_VISIBLE | WS_CHILD, 215, 90, 75, 35, windowHWND, (HMENU)BUTTON_WHOLEPERIOD, hPrevInstance, NULL);
	hStatistics = CreateWindowW(L"Button", L"Stats", WS_VISIBLE | WS_CHILD, 215, 130, 75, 35, windowHWND, (HMENU)BUTTON_STAT, hPrevInstance, NULL);
}