#include "camera.h"

camera::camera() {
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
	veloc = 
	while (1) {

		re.ca.update();
		re.update_ca();
		Sleep(dt1);
	}
}

void camera::jump(render* ren) {
	if ()
	_beginthread(jumping, 0, ren);
}

void camera::rotate(float x, float y) {
	XMMATRIX m = XMMatrixRotationAxis(up, x);
	LookAt = XMVector3TransformCoord(LookAt, m);
	R = XMVector3Cross(LookAt, up);
	m = XMMatrixRotationAxis(R, y);
	LookAt = XMVector3TransformCoord(LookAt, m);
	update();
}