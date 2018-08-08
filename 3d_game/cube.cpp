#include "cube.h"

void thread1(void*);

cube::cube() {
	move(XMVectorSet(0, 1001, 0, 0));
	V[0] = XMVectorSet(-1, 1, -1, 0) * 1000;
	V[1] = XMVectorSet(1, 1, -1, 0) * 1000;
	V[2] = XMVectorSet(1, -1, -1, 0) * 1000;
	V[3] = XMVectorSet(-1, -1, -1, 0) * 1000;
	V[4] = XMVectorSet(-1, 1, 1, 0) * 1000;
	V[5] = XMVectorSet(1, 1, 1, 0) * 1000;
	V[6] = XMVectorSet(1, -1, 1, 0) * 1000;
	V[7] = XMVectorSet(-1, -1, 1, 0) * 1000;
	for (int i = 0; i < 8; i++)
		V[i] += XMVectorSet(0, (float)1000.01, 0, 0);
	handle = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)thread1, this, 0, NULL);
}

void thread1(void* arg) {
	cube& cur = *(cube*)arg;
	while (1) {
		Sleep(dt1);
		double t = (double)dt1 / 1000;
		float y = XMVectorGetY(cur.veloc);
		XMVectorSetY(cur.veloc, y + accel * t);
		move(XMVectorSet(0, y * t, 0, 0));
	}
}

cube::~cube() {
	CloseHandle((HANDLE)handle);
}

void cube::move(XMVECTOR v) {
	for (int i = 0; i < 8; i++)
		V[i] += v;
	for (int i = 0; i < 8; i++)
		if (XMVectorGetY(V[i]) < 0) {
			for (int i = 0; i < 8; i++)
				V[i] -= v;
			return;
		}
}

void cube::cal() {
	chD.clear(); chDL.clear(); planeDL.clear();
	D.clear(); DL.clear();

	for (int i = 0; i < 8; i++)
		VV[i] = XMVector3TransformCoord(V[i], M);
	for (int i = 0; i < 8; i++) {
		XMVECTOR v = VV[i];
		double X, Y;
		X = (XMVectorGetX(v) / XMVectorGetZ(v) / tanf(90 / 2) * 1000 + 1980 / 2);
		Y = (XMVectorGetY(v) / XMVectorGetZ(v) / tanf(90 / 2) * 1000 + 1080 / 2);
		DOT d = { X,Y };
		D.push_back(d);
	}
	chD = convex_hull(D);
	chD.push_back(chD[0]);

	for (int i = 0; i < chD.size() - 1; i++)
		chDL.push_back(get_a_b(chD[i], chD[i + 1]));
	chDL.push_back(chDL[0]);

	VD temp;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			DOT& a = D[index[i][j]];
			DOT& b = D[index[i][j + 1]];
			DOT d = get_a_b(a, b);
			temp.push_back(d);
		}
		planeDL.push_back(temp);
		temp.clear();
	}
}