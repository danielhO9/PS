#include <bits/stdc++.h>
using namespace std;

int cache[10][10000];
int s[10000][2];
int n;

int matchCache(int l, int i) {
	int now = (s[i][0] + l) % 10;
	if (i == n - 1) return min(abs(now - s[i][1]), 10 - abs(now - s[i][1]));
	int& ret = cache[l][i];
	if (ret != -1) return ret;
	ret = INT32_MAX;
	ret = min(ret, matchCache(l, i + 1) + (now + 10 - s[i][1]) % 10);
	ret = min(ret, matchCache((l + (s[i][1] + 10 - now) % 10) % 10, i + 1) + (s[i][1] + 10 - now) % 10);
	return ret;
}

void generator(int l, int i) {
	int now = (s[i][0] + l) % 10;
	cout << i + 1 << ' ';
	if (i == n - 1) {
		if ((now + 10 - s[i][1]) % 10 < (s[i][1] + 10 - now) % 10) cout << -((now + 10 - s[i][1]) % 10);
		else cout << (s[i][1] + 10 - now) % 10;
		return;
	}
	if (matchCache(l, i) == matchCache(l, i + 1) + (now + 10 - s[i][1]) % 10) {
		cout << -((now + 10 - s[i][1]) % 10) << '\n';
		generator(l, i + 1); return;
	} else {
		cout << (s[i][1] + 10 - now) % 10 << '\n';
		generator((l + (s[i][1] + 10 - now) % 10) % 10, i + 1); return;
	}
}

void solve() {
	cin >> n;
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < n; ++j) {
			char c; cin >> c;
			s[j][i] = c - '0';
		}
	}
	memset(cache, -1, sizeof(cache));
	cout << matchCache(0, 0) << '\n';
	generator(0, 0);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}