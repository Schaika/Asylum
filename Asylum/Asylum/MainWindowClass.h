#pragma once
#include <Windows.h>
class MainWindowClass
{
public:
	MainWindowClass(HINSTANCE p_hInstance, WNDPROC p_WindowProcedure, LPCUWSTR p_windowName, int p_width = 800, int p_height = 600);
	~MainWindowClass();
	HWND getHWND() { return windowHWND; };
	void handleMenu(HWND hWnd, UINT message, WPARAM wp, LPARAM lp);
	HWND hListBox = NULL;
	HWND hScore = NULL;
	HWND hNextDayButton = NULL;
	HWND hWholePeriodButton = NULL;
	HWND hStatistics = NULL;
	HWND hDays = NULL;
	HWND hCapacity = NULL;
private:
	WNDCLASSW windowClass = { 0 };
	HWND windowHWND = NULL;
	HINSTANCE hPrevInstance = NULL;
	void initMenu();
	void initControls();
};

