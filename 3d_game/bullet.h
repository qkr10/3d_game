#pragma once
#include "calc.h"

class bullet : private calc {
private:
	XMVECTOR rear, dir, front;
	unsigned int handle;
	void* P;
public:
	DOT r, f;
	bullet();
	bullet(XMVECTOR, XMVECTOR, void*);
	void move();
	void check_collision();
};