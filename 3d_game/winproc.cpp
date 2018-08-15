#include "declare.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		handling_WM_CREATE(hWnd, uMsg, wParam, lParam);
		break;
	case WM_PAINT:
		handling_WM_PAINT(hWnd, uMsg, wParam, lParam);
		break;
	case WM_MOUSEMOVE:
		handling_WM_MOUSEMOVE(hWnd, uMsg, wParam, lParam);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		exit(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}