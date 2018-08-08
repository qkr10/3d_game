#pragma once
#include <Windows.h>
#include <vector>
#include <algorithm>
#include "render.h"

/* 함수 선언 */
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void handling_WM_CREATE(HWND, UINT, WPARAM, LPARAM);
void handling_WM_PAINT(HWND, UINT, WPARAM, LPARAM);
void handling_WM_MOUSEMOVE(HWND, UINT, WPARAM, LPARAM);

void Key_Check(HWND, UINT, UINT_PTR, DWORD);

int inline _key(char C) { return GetAsyncKeyState(C) & 0x8000; }
int inline _key1(char C) { return (GetAsyncKeyState(C) & 0x8001) == 0x8001; }