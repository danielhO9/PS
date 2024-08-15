#include <bits/stdc++.h>
using namespace std;

int H, W;
int marked[20][20];
int cache[20][20][20][20];

int grundy(int y1, int x1, int y2, int x2) {
	if (y1 > y2 || x1 > x2) return 0;
	int& ret = cache[y1][x1][y2][x2];
	if (ret != -1) return ret;
	set<int> s;
	for (int i = y1; i <= y2; ++i) {
		for (int j = x1; j <= x2; ++j) {
			if (marked[i][j]) continue;
			int tmp = grundy(y1, x1, i - 1, j - 1) ^ grundy(y1, j + 1, i - 1, x2) ^ grundy(i + 1, x1, y2, j - 1) ^ grundy(i + 1, j + 1, y2, x2);
			s.insert(tmp);
		}
	}
	ret = 0;
	while (s.find(ret) != s.end()) ++ret;
	return ret;
}

void solve() {
	cin >> H >> W;
	for (int i = 0; i < H; ++i) {
		string tmp; cin >> tmp;
		for (int j = 0; j < W; ++j) {
			marked[i][j] = (tmp[j] == 'X');
		}
	}
	memset(cache, -1, sizeof(cache));
	if (grundy(0, 0, H - 1, W - 1)) cout << "First";
	else cout << "Second";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}