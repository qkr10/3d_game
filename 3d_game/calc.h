#pragma once
#include <Windows.h>
#include <synchapi.h>
#include <DirectXMath.h>
#include <vector>
#include <algorithm>
#include <process.h>

using namespace DirectX;
using namespace std;

/* 상수 선언 */
const int dt1 = 20; //ms
const int dt2 = 30;
const int accel = -50;
const int monitor_x = 1980, monitor_y = 1080;
const int index[6][5] = {
	{ 0,1,2,3,0 },
	{ 5,4,7,6,5 },
	{ 3,7,4,0,3 },
	{ 1,5,6,2,1 },
	{ 4,5,1,0,4 },
	{ 7,3,2,6,7 }
};

/* 구조체 선언*/
struct DOT {
	double x, y;
	DOT operator+ (DOT r) {
		return{ x + r.x, y + r.y };
	}
	template <typename T>
	DOT operator/ (T r) {
		return{ x / r, y / r };
	}
};

/* typedef */
typedef vector<DOT> VD;
typedef vector<VD> VVD;
typedef pair<DOT, DOT> DD;
typedef vector<DD> VDD;
typedef pair<double, double> R;
typedef vector<R> VR;
typedef vector<VR> VVR;
typedef vector<int> VI;
typedef vector<XMVECTOR> VV;

class calc
{
public:
	static double cross(DOT, DOT, DOT);
	static double scale(DOT);
	static double angle(DOT, DOT, DOT);
	static double length(DD);
	static DOT point(DOT, DOT);
	static bool winding_num(VD&, DOT);
	static bool judge(DD&, DD&);
	static bool point_check(DOT, DOT, DOT);
	static VD convex_hull(VD);
	static DOT get_a_b(DOT, DOT);
};