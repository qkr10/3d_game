#include "bullet.h"
#include "render.h"

bullet::bullet() {
	return;
}

bullet::bullet(XMVECTOR R, XMVECTOR D, void* p, XMMATRIX* m) : erase(false), M(m), P(p), rear(R) {
	const static float length = 1000;
	dir = XMVector3Normalize(D);
	front = R + dir * 1000;
	XMVECTOR temp = rear - front;
	pre_time = time = GetTickCount64();
	calc();
}

bool bullet::check_collision() {
	vector<cube>& cu = (*(render*)P).cu;
	for (int i = 0; i < cu.size(); i++) {
		cube& it = cu[i];
		for (int i = 0; i < 6; i++) {
			XMVECTOR plane = XMPlaneFromPoints(it.VV[index[i][0]], it.VV[index[i][1]], it.VV[index[i][2]]);
			XMVECTOR point = XMPlaneIntersectLine(plane, rear, front);
			XMVECTOR temp = (rear + front) / 2;
			if (XMVector3InBounds(point - temp, front - temp)) {
				//큐브의 체력감소
				return true;
			}
		}
	}
	return false;
}

void bullet::move() {
	const static float dist = 10000;
	XMVECTOR temp = dir * dist * (GetTickCount64() - pre_time) / 1000;
	pre_time = GetTickCount64();
	rear += temp;
	front += temp;
}

void bullet::calc() {
	move();
	if (check_collision())
		erase = true;
	if (GetTickCount64() - time > 3000)
		erase = true;
	XMVECTOR R = XMVector3TransformCoord(rear, *M);
	XMVECTOR F = XMVector3TransformCoord(front, *M);
	double X, Y;
	X = (XMVectorGetX(R) / XMVectorGetZ(R) / tanf(90 / 2) * 1000 + 1980 / 2);
	Y = (XMVectorGetY(R) / XMVectorGetZ(R) / tanf(90 / 2) * 1000 + 1080 / 2);
	r = { X,Y };
	X = (XMVectorGetX(F) / XMVectorGetZ(F) / tanf(90 / 2) * 1000 + 1980 / 2);
	Y = (XMVectorGetY(F) / XMVectorGetZ(F) / tanf(90 / 2) * 1000 + 1080 / 2);
	f = { X,Y };
}