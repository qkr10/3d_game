#include "camera.h"
#include "render.h"

camera::camera() {
	up = XMVectorSet(0, -1, 0, 0);
	V = XMVectorSet(10, (float)2700.01, -8000, 0);
	R = XMVectorSet(1, 0, 0, 0);
	LookAt = XMVectorSet(0, 0, 1, 0);
	veloc = XMVectorZero();
	trigger = false;
	update();
}

void camera::update() {
	M = XMMatrixLookAtLH(V, LookAt + V, up);
}

void camera::moves(float f) {
	V += R * f;
	update();
}

void camera::movef(float f) {
	V += XMVector3Cross(R, XMVectorSet(0, 1, 0, 0)) * f;
	update();
}

void jumping(void* arg) {
	render& re = *(render*)arg;
	re.ca.veloc = XMVectorSet(0, 5500, 0, 0);
	while (1) {
		re.ca.V += re.ca.veloc * dt1 / 1000;
		if (XMVectorGetY(re.ca.V) < 2700) {
			re.ca.V -= re.ca.veloc * dt1 / 1000;
			break;
		}
		re.ca.veloc += XMVectorSet(0, accel * dt1 / 1000, 0, 0);
		re.ca.update();
		re.update_ca();
		Sleep(dt1);
	}
	re.ca.trigger = false;
}

void camera::jump(void* ren) {
	if (!trigger) {
		_beginthread(jumping, 0, ren);
		trigger = true;
	}
}

void camera::rotate(float x, float y) {
	XMMATRIX m = XMMatrixRotationAxis(up, x);
	LookAt = XMVector3TransformCoord(LookAt, m);
	R = XMVector3Cross(LookAt, up);
	m = XMMatrixRotationAxis(R, y);
	LookAt = XMVector3TransformCoord(LookAt, m);
	update();
}