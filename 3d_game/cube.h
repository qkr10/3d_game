#pragma once
#include "calc.h"

class cube : private calc {
private:
	XMVECTOR V[8];
	unsigned int handle;
public:
	XMVECTOR VV[8];
	XMMATRIX M;
	VD D, DL, chD, chDL;
	VVD planeD;
	VI F;
	XMVECTOR veloc = XMVectorSet(0, 100, 0, 0);
	cube();
	void move(XMVECTOR);
	void cal();
};