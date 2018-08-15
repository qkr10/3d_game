#pragma once
#include "calc.h"

class bullet : private calc {
private:
	XMMATRIX* M;
public:
	XMVECTOR rear, dir, front;
	void* P;
	bool erase;
	unsigned long long time, pre_time;
	DOT r, f;
	bullet();
	bullet(XMVECTOR, XMVECTOR, void*, XMMATRIX*);
	void move();
	void calc();
	bool check_collision();
};