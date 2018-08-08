#include "declare.h"

render renderer;

void handling_WM_CREATE(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	SetTimer(hWnd, 4, 1000 / 50, (TIMERPROC)Key_Check);
	renderer.hWnd = hWnd;
	return;
}

void handling_WM_PAINT(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC h_dc = BeginPaint(hWnd, &ps);

	//더블버퍼링
	RECT client_size; GetClientRect(hWnd, &client_size);
	HDC hdc = CreateCompatibleDC(h_dc);
	HBITMAP mem_new = CreateCompatibleBitmap(h_dc, client_size.right, client_size.bottom);
	HBITMAP mem_old = (HBITMAP)SelectObject(hdc, mem_new);

	//하이얀 펜을 준비
	HPEN whiteP, redP, grayP, oldP;
	whiteP = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	redP = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	grayP = CreatePen(PS_SOLID, 2, RGB(127, 127, 127));
	oldP = (HPEN)SelectObject(hdc, whiteP);

	VDD dots(renderer.dots);
	for (VDD::iterator it = dots.begin(); it != dots.end(); it++) {
		MoveToEx(hdc, it->first.x, it->first.y, NULL);
		LineTo(hdc, it->second.x, it->second.y);
	}

	SelectObject(hdc, oldP);

	BitBlt(h_dc, 0, 0, client_size.right, client_size.bottom, hdc, 0, 0, SRCCOPY);
	mem_new = (HBITMAP)SelectObject(hdc, mem_old);

	DeleteObject(mem_new);
	DeleteDC(hdc);
	EndPaint(hWnd, &ps);
	return;
}

void handling_WM_MOUSEMOVE(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	POINT P;
	GetCursorPos(&P);
	FLOAT Angle_x = XMConvertToRadians((monitor_x / 2 - P.x) * (float)0.1);
	FLOAT Angle_y = XMConvertToRadians((monitor_y / 2 - P.y) * (float)0.1);
	SetCursorPos(monitor_x / 2, monitor_y / 2);
	renderer.ca.rotate(Angle_x, Angle_y);
	renderer.update_ca();
	return;
}

void Key_Check(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	if (_key(VK_ESCAPE))
		DestroyWindow(hWnd);
	if (_key('D')) {
		renderer.ca.moves(-100);
		renderer.update_ca();
	}
	if (_key('A')) {
		renderer.ca.moves(100);
		renderer.update_ca();
	}
	if (_key('S')) {
		renderer.ca.movef(-100);
		renderer.update_ca();
	}
	if (_key('W')) {
		renderer.ca.movef(100);
		renderer.update_ca();
	}
	if (_key1(VK_SPACE))
		renderer.ca.jump(&renderer);
	if (_key1(VK_TAB));
	return;
}