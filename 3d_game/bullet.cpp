#include "bullet.h"
#include "render.h"

void thread3(void*);

bullet::bullet() {
	return;
}

bullet::bullet(XMVECTOR R, XMVECTOR D, void* p) {
	const static float length = 1000;
	P = p;
	rear = R;
	dir = XMVector3Normalize(D);
	front = R + dir * 1000;
	handle = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)thread3, this, 0, NULL);
}

void bullet::check_collision() {
	vector<cube>& cu = ((render*)P)->cu;
	vector<cube>::iterator it = cu.begin();
	for (; it != cu.end; it++) {
		
	}
}

void bullet::move() {
	const static float dist = 10;
	XMVECTOR temp = dir * dist;
	rear += temp;
	front += temp;
}

void thread3(void* arg) {
	const static int ms = 70;
	bullet& b = *(bullet*)arg;
	while (1) {
		Sleep(ms);
		b.move();
		b.check_collision();
	}
}