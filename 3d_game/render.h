#pragma once
#include "cube.h"
#include "camera.h"
#include "bullet.h"

class render : private calc {
private:
	unsigned int handle;
public:
	vector<cube> cu;
	queue<bullet> bu;
	camera ca;
	VDD dots, buls;
	HWND hWnd;
	render();
	void update_ca();
	void rendering();
	void shoot();
};