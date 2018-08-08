#pragma once
#include "calc.h"
#include "render.h"

class camera : private calc {
private:
	XMVECTOR up = XMVectorSet(0, -1, 0, 0);
	XMVECTOR V = XMVectorSet(10, (float)700.01, -8000, 0);
	XMVECTOR R = XMVectorSet(1, 0, 0, 0);
	XMVECTOR LookAt = XMVectorSet(0, 0, 1, 0);
	XMVECTOR veloc = XMVectorZero();
public:
	unsigned int handle;
	XMMATRIX M;
	camera();
	void update();
	void moves(float);
	void movef(float);
	void jump(render*);
	void rotate(float, float);
};