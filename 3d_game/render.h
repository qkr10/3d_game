#pragma once
#include "cube.h"
#include "camera.h"

class render : private calc {
private:
	vector<cube> cu;
	unsigned int handle;
public:
	camera ca;
	VDD dots;
	HWND hWnd;
	render();
	void update_ca();
	void rendering();
};