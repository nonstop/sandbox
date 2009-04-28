#pragma once

#include "resource.h"

struct TPoint
{
	float x;
	float y;
};

bool IsRunning(HANDLE &hMutex);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void Init();
void Shutdown();
void Display();
void SetView();
