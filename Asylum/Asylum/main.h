#pragma once
#include <Windows.h>
#include "MainWindowClass.h"
#include "AsylumHandler.h"
#include "InitialValues.h"
MainWindowClass* MainWindow = NULL;
AsylumHandler* Asylum = NULL;
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void initAsylumHandler();
void drawUI();
void setScoreUI(double score);