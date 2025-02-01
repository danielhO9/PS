#include <bits/stdc++.h>
using namespace std;

int N;
int dif[101][3];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i = 1; i <= N; ++i) {
		int d; string nm, df;
		cin >> d >> nm >> df;
		if (nm == "Mildred") {
			dif[d][0] += stoi(df);
		} else if (nm == "Elsie") {
			dif[d][1] += stoi(df);
		} else {
			dif[d][2] += stoi(df);
		}
	}
	int cur = 7;
	int ans = 0;
	int val[3] = {7, 7, 7};
	for (int i = 1; i <= 100; ++i) {
		for (int j = 0; j < 3; ++j) val[j] += dif[i][j];
		int mx = -1;
		for (int j = 0; j < 3; ++j) mx = max(mx, val[j]);
		int nxt = 0;
		for (int j = 0; j < 3; ++j) if (mx == val[j]) nxt += (1 << j);
		if (nxt != cur) ++ans;
		cur = nxt;
	}
	cout << ans;
}