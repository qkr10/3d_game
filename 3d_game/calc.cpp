#include "calc.h"

double calc::cross(DOT O, DOT A, DOT B) {
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

double calc::scale(DOT A) {
	return sqrt(A.x * A.x + A.y * A.y);
}

double calc::angle(DOT A, DOT O, DOT B) {
	A.x -= O.x;
	A.y -= O.y;
	B.x -= O.x;
	B.y -= O.y;
	float dot = A.x * B.x + A.y * B.y;
	return acos(dot / scale(A) / scale(B));
}

double calc::length(DD A) {
	DOT& a = A.second;
	DOT& b = A.first;
	return scale({ a.x - b.x, a.y - b.y });
}

DOT calc::point(DOT A, DOT B) {
	double x = (B.y - A.y) / (A.x - B.x);
	double y = x * A.x + A.y;
	return{ x, y };
}

bool calc::winding_num(VD& ch, DOT d)
{
	double sum = 0;
	for (int i = 0; i < ch.size() - 1; i++) {
		if (cross(d, ch[i], ch[i + 1]) > 0)
			sum += angle(ch[i], d, ch[i + 1]);
		else sum -= angle(ch[i], d, ch[i + 1]);
	}
	return abs(sum - 2 * (double)3.141592) < 0.001;
}

bool calc::judge(DD& A, DD& B) {
	return length(A) < length(B);
}

bool calc::point_check(DOT O, DOT A, DOT B) {
	if (A.x < B.x) {
		if (A.x < O.x && O.x < B.x)
			return true;
	}
	else if (B.x < O.x && O.x < A.x)
		return true;
	return false;
}

VD calc::convex_hull(VD D) {
	int k = 0;
	VD H(16);
	sort(D.begin(), D.end(), [](DOT& a, DOT& b) {return a.x < b.x; });

	for (int i = 0; i < 8; ++i) {
		while (k >= 2 && cross(H[k - 2], H[k - 1], D[i]) <= 0) k--;
		H[k++] = D[i];
	}
	for (int i = 7, t = k + 1; i > 0; --i) {
		while (k >= t && cross(H[k - 2], H[k - 1], D[i - 1]) < 0) k--;
		H[k++] = D[i - 1];
	}

	H.resize(k - 1);
	return H;
}

DOT calc::get_a_b(DOT A, DOT B)
{
	double a, b;
	a = (A.y - B.y) / (A.x - B.x + 0.000001);
	b = -1 * A.x * a + A.y;
	return{ a, b };
}