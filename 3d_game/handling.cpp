#include "declare.h"

render renderer;

void handling_WM_CREATE(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	SetTimer(hWnd, 1, 20, (TIMERPROC)Key_Check);
	SetTimer(hWnd, 2, 30, (TIMERPROC)rendering);
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
	HPEN whiteP, yellowP, grayP, oldP;
	whiteP = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	yellowP = CreatePen(PS_SOLID, 2, RGB(255, 255, 0));
	grayP = CreatePen(PS_SOLID, 2, RGB(127, 127, 127));

	oldP = (HPEN)SelectObject(hdc, whiteP);
	VDD dots(renderer.dots);
	for (VDD::iterator it = dots.begin(); it != dots.end(); it++) {
		MoveToEx(hdc, it->first.x, it->first.y, NULL);
		LineTo(hdc, it->second.x, it->second.y);
	}

	SelectObject(hdc, yellowP);
	VDD buls(renderer.buls);
	for (VDD::iterator it = buls.begin(); it != buls.end(); it++) {
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

void handling_WM_MOUSEMOVE(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	POINT P;
	GetCursorPos(&P);
	FLOAT Angle_x = XMConvertToRadians((P.x - monitor_x / 2) * (float)0.1);
	FLOAT Angle_y = XMConvertToRadians((P.y - monitor_y / 2) * (float)0.1);
	SetCursorPos(monitor_x / 2, monitor_y / 2);
	renderer.ca.rotate(Angle_x, Angle_y);
	renderer.update_ca();
	return;
}

void Key_Check(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	if (_key1(VK_LBUTTON))
		renderer.shoot();
	if (_key(VK_ESCAPE))
		DestroyWindow(hWnd);
	if (_key('D')) {
		renderer.ca.moves(-200);
		renderer.update_ca();
	}
	if (_key('A')) {
		renderer.ca.moves(200);
		renderer.update_ca();
	}
	if (_key('S')) {
		renderer.ca.movef(-200);
		renderer.update_ca();
	}
	if (_key('W')) {
		renderer.ca.movef(200);
		renderer.update_ca();
	}
	if (_key1(VK_SPACE))
		renderer.ca.jump(&renderer);
	if (_key1(VK_TAB));
	return;
}

void rendering(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	render& cur = renderer;
	for each (auto var in cur.bu._Get_container())
		var.calc();
	if (!cur.bu.empty())
		if (cur.bu.front().erase)
			cur.bu.pop();
	cur.rendering();
	InvalidateRect(cur.hWnd, NULL, true);
}