#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

int H, W;
int cache[1000][1000];
char a[1000][1000];

int matchCache(int i, int j) {
	if (i == 0 && j == 0) return 1;
	int& ret = cache[i][j];
	if (ret != -1) return ret;
	ret = 0;
	if (a[i][j] == '#') return ret;
	if (i - 1 >= 0) {
		ret += matchCache(i - 1, j);
		ret %= MOD;
	}
	if (j - 1 >= 0) {
		ret += matchCache(i, j - 1);
		ret %= MOD;
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	memset(cache, -1, sizeof(cache));
	cin >> H >> W;
	for (int i = 0; i < H; ++i) {
		string s; cin >> s;
		for (int j = 0; j < W; ++j) a[i][j] = s[j];
	}
	cout << matchCache(H - 1, W - 1);
}