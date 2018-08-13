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
	VDD dots;
	HWND hWnd;
	render();
	~render();
	void update_ca();
	void rendering();
	void shoot();
};