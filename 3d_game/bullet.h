#pragma once
#include "calc.h"

class bullet : private calc {
private:
	XMVECTOR rear, dir, front;
	unsigned int handle;
public:
	void* P;
	bool erase;
	DOT r, f;
	bullet();
	bullet(XMVECTOR, XMVECTOR, void*);
	void move();
	bool check_collision();
};