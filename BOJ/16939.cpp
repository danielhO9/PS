#include <bits/stdc++.h>
using namespace std;

int c[25];
int tc[25];

int check() {
	for (int i = 1; i <= 24; ++i) {
		if (tc[i] != tc[((i - 1) / 4) * 4 + 1]) return 0;
	}
	return 1;
}

vector<int> pos[6] = {
	{2, 4, 6, 8, 10, 12, 23, 21},
	{1, 3, 5, 7, 9, 11, 24, 22},
	{13, 14, 5, 6, 17, 18, 21, 22},
	{15, 16, 7, 8, 19, 20, 23, 24},
	{3, 4, 17, 19, 10, 9, 16, 14},
	{1, 2, 18, 20, 12, 11, 15, 13}
};

int rotate(int p, int dif) {
	for (int i = 1; i <= 24; ++i) tc[i] = c[i];
	for (int i = 0; i < 8; ++i) tc[pos[p][i]] = c[pos[p][(i + dif + 8) % 8]];
	return check();
}

void solve() {
	for (int i = 1; i <= 24; ++i) cin >> c[i];
	int ans = 0;
	for (int i = 0; i < 6; ++i) {
		ans |= rotate(i, 2);
		ans |= rotate(i, -2);
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}