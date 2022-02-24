#include "main.h"
#include "Menuing.h"
#include <Strsafe.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	MainWindow = new MainWindowClass(hInstance, WindowProcedure, L"BigDicks WinAPI",800,485);
	initAsylumHandler();
	MSG receivedMessage = { 0 };
	while (GetMessage(&receivedMessage,NULL,NULL,NULL))
	{
		TranslateMessage(&receivedMessage);
		DispatchMessage(&receivedMessage);
	}

	return 0;
};

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wp, LPARAM lp) {
	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wp))
		{
		case MENU_OPEN:
			for (int i = 0; i < 15; i++) {
				MessageBeep(MB_ICONERROR);
				Sleep(75);
			}
			break;
		case MENU_ABOUT:
			MessageBoxW(NULL, L"Папа, ты говоришь, семья – это маленькое государство. А кто ты?!\n— Президент, конечно!\n— А мама?!\n— Власть.\n— А бабушка?!\n— ФСБ!\n— А я кто же? \n— А ты… Ты народ!\nЧерез час Вовочка звонит отцу на работу : \n— Я всем рассказал, что у нас в государстве президент ебет народ", L"About", MB_OK);
			break;
		case MENU_EXIT:
			DestroyWindow(hWnd);
			break;
		case MENU_OPENLINK:
			ShellExecute(NULL, L"open", L"https://youtu.be/xQMLg0VEm2c", NULL, NULL, SW_SHOWNORMAL);
			break;
		case MENU_CHANGETITLE:
			break;
		case LISTBOX_ITEM:
			switch (HIWORD(wp))
			{
				case LBN_SELCHANGE:
					{
						HWND hwndList = MainWindow->hListBox;
						int lbItem = (int)SendMessage(hwndList, LB_GETCURSEL, 0, 0);
						int i = (int)SendMessage(hwndList, LB_GETITEMDATA, lbItem, 0);
						double score = Asylum->getList().at(i)->getScore();
						setScoreUI(score);
					}
				break;

				default:
					break;
			}
			break;
		case BUTTON_NEXTDAY:
			Asylum->nextDay();
			drawUI();
			break;
		case BUTTON_WHOLEPERIOD:
			for(int i=0; i<365;i++) Asylum->nextDay();
			drawUI();
			break;
		case BUTTON_STAT:
			Asylum->showStats();
			break;
		default:
			break;
		}
		break;
	case WM_CREATE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProcW(hWnd, message, wp, lp);
	}
	return 0;
}


void initAsylumHandler() {
	Asylum = new AsylumHandler();
	Asylum->start();
	drawUI();
}

void drawUI()
{
	HWND hwndList = MainWindow->hListBox;
	wchar_t name[255];
	int nameSize=0;
	auto list = Asylum->getList();
	{
		int lbItem = (int)SendMessage(hwndList, LB_GETCURSEL, 0, 0);
		if (lbItem != LB_ERR) nameSize = SendMessageW(hwndList, LB_GETTEXT, lbItem, (LPARAM)name);
	}
	
	SendMessage(hwndList, LB_RESETCONTENT, NULL, NULL);
	for (int i = 0; i < list.size(); i++) {
		auto obj = list.at(i);
		int pos = SendMessageW(hwndList, LB_ADDSTRING, NULL, (LPARAM)obj->getName().c_str());
		SendMessage(hwndList, LB_SETITEMDATA, pos, (LPARAM)i);
		SetFocus(hwndList);
	}
	if (nameSize > 0) {
		int lbItem = (int)SendMessageW(hwndList, LB_SELECTSTRING, NULL, (LPARAM)name);
		if (lbItem != LB_ERR) {
			int i = (int)SendMessage(hwndList, LB_GETITEMDATA, lbItem, 0);
			double score = list.at(i)->getScore();
			setScoreUI(score);
		}
	}
	{
		//дни
		wchar_t buffer[255];
		StringCbPrintfW(buffer, 255, L"%d", Asylum->getDays());
		SetWindowTextW(MainWindow->hDays, buffer);
	}
	{
		//вместимость
		wchar_t buffer[255];
		StringCbPrintfW(buffer, 255, L"%d/%d", Asylum->getList().size(),InitialValues.N1);
		SetWindowTextW(MainWindow->hCapacity, buffer);
	}
}

void setScoreUI(double score)
{
	wchar_t buffer[255];
	StringCbPrintfW(buffer, 255, L"%.2f", score);
	SetWindowTextW(MainWindow->hScore, buffer);
}
