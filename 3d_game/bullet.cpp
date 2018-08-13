#include "bullet.h"
#include "render.h"

void thread3(void*);

bullet::bullet() {
	return;
}

bullet::bullet(XMVECTOR R, XMVECTOR D, void* p) : erase(false) {
	const static float length = 1000;
	P = p;
	rear = R;
	dir = XMVector3Normalize(D);
	front = R + dir * 1000;
	XMVECTOR temp = rear - front;
	handle = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)thread3, this, 0, NULL);
}

bool bullet::check_collision() {
	vector<cube>& cu = ((render*)P)->cu;
	vector<cube>::iterator it = cu.begin();
	for (; it != cu.end(); it++) {
		for (int i = 0; i < 6; i++) {
			XMVECTOR plane = XMPlaneFromPoints(it->VV[index[i][0]], it->VV[index[i][1]], it->VV[index[i][2]]);
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
	const static float dist = 10;
	XMVECTOR temp = dir * dist;
	rear += temp;
	front += temp;
}

void thread3(void* arg) {
	const static int ms = 70, del_ms = 3000;
	bullet& b = *(bullet*)arg;
	for (int i = 0; i < del_ms / ms; i++) {
		Sleep(ms);
		b.move();
		if (b.check_collision())
			break;
	}
	b.erase = true;
}