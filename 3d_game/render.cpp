#include "render.h"

void thread2(void *arg);

render::render() {
	cu.assign(1, cube());
	cu[0].M = ca.M;
	handle = _beginthread(thread2, 0, this);
}

void thread2(void* arg) {
	render& cur = *(render*)arg;
	while (1) {
		cur.rendering();
		InvalidateRect(cur.hWnd, NULL, true);
		Sleep(dt2);
	}
}

void render::update_ca() {
	vector<cube>::iterator it = cu.begin();
	for (; it != cu.end(); it++)
		it->M = ca.M;
}

void render::rendering() {
	int s = cu.size(), val = 0;
	vector<int> t(s, val);
	vector<vector<int>> dp(s, t);
	dots.clear();
	for (int i = 0; i < s; i++)
		cu[i].cal();
	//동적계획법 이용
	//어떤물체가 어떤물체를 가리는지 판단
	for (int n = 0; n < s; n++)
		for (int m = 0; m < s; m++) {
			if (n == m || dp[n][m] == 1) continue;
			for (int i = 0; i < cu[n].D.size(); i++)
				if (winding_num(cu[n].chD, cu[m].D[i])) {
					dp[n][m] = 1;
					dp[m][n] = 1;
					//LOG_print(L"\r\n물체끼리 가려짐!");
					XMVECTOR center
						= (cu[n].VV[index[0][0]]
							+ cu[n].VV[index[0][2]]
							+ cu[n].VV[index[2][0]]
							+ cu[n].VV[index[2][2]]) / 4;
					double L = XMVectorGetX(XMVector3Length(cu[m].VV[i]));
					double D = XMVectorGetX(XMVector3Dot(center, cu[m].VV[i]));
					if (D < L * L)
						cu[m].F.push_back(n);
					else
						cu[n].F.push_back(m);
				}
		}

	for (int m = 0; m < cu.size(); m++) {
		for (int i = 0; i < 6; i++) {
			//은면제거
			XMVECTOR v1 = cu[m].VV[index[i][0]], v2 = cu[m].VV[index[i][1]],
				v3 = cu[m].VV[index[i][2]], v4 = cu[m].VV[index[i][3]];
			XMVECTOR normal = XMVector3Cross(v1 - v2, v1 - v4);
			if (XMVectorGetX(XMVector3Dot(normal, (v1 * 3 / 2) - (v2 / 2))) > 0)
				continue;
			if (XMVectorGetZ(v1) < 0 || XMVectorGetZ(v2) < 0 || XMVectorGetZ(v3) < 0 || XMVectorGetZ(v4) < 0)
				continue;

			for (int j = 0; j < 4; j++) {
				cu[m].planeD[i].push_back(cu[m].D[index[i][j]]);
				VDD temp;
				for (int k = 0; k < cu[m].F.size(); k++)
					for (int l = 0; l < cu[cu[m].F[k]].chDL.size(); l++) {
						DOT P = point(cu[m].planeD[i][j], cu[cu[m].F[k]].chDL[l]);
						if (point_check(P, cu[m].D[index[i][j]], cu[m].D[index[i][j + 1]]))
							temp.push_back(make_pair(P, cu[m].D[index[i][j]]));
					}
				if (temp.size() > 1)
					sort(temp.begin(), temp.end(), judge);
				for (int k = 0; k < temp.size(); k++)
					cu[m].planeD[i].push_back(temp[k].first);
			}
			cu[m].planeD[i].push_back(cu[m].planeD[i][0]);

			for (int k = 0; k < cu[m].planeD[i].size() - 1; k++) {
				int R = 0;
				for (int l = 0; l < cu[m].F.size(); l++)
					if (winding_num(cu[cu[m].F[l]].chD, (cu[m].planeD[i][k] + cu[m].planeD[i][k + 1]) / 2))
						R++;
				if (R == 0)
					dots.push_back(make_pair(cu[m].planeD[i][k], cu[m].planeD[i][k + 1]));
			}
		}
	}
}