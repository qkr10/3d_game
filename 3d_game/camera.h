#pragma once
#include "calc.h"

class camera : private calc {
private:
	XMVECTOR up;
	XMVECTOR R;
public:
	XMVECTOR V;
	XMVECTOR LookAt;
	XMVECTOR veloc;
	bool trigger;
	XMMATRIX M;
	camera();
	void update();
	void moves(float);
	void movef(float);
	void jump(void*);
	void rotate(float, float);
};