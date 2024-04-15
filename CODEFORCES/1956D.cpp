#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
int a[18];
int sum[18];

int cache[18];
int zcnt[18];
int maxgen[18];
int makecnt[19];

int matchCache(int i) {
	if (i == 0) {
		if (a[i] == 0) return 1;
		else return a[i];
	}
	int& ret = cache[i];
	if (ret != -1) return ret;
	ret = max((i + 1) * (i + 1), sum[i]);
	maxgen[i] = 0;
	for (int j = 0; j < i; ++j) {
		if (ret < matchCache(j) + max((i - j) * (i - j), sum[i] - sum[j])) {
			maxgen[i] = j + 1;
			ret = matchCache(j) + max((i - j) * (i - j), sum[i] - sum[j]);
		}
	}
	return ret;
}

void generator(int l, int r) {
	if (l == r) {
		cout << l + 1 << ' ' << r + 1 << '\n';
		return;
	}
	if (l + 1 == r) {
		cout << r + 1 << ' ' << r + 1 << '\n';
		cout << l + 1 << ' ' << r + 1 << '\n';
		return;
	}
	for (int i = r; i > l; --i) {
		generator(l + 1, i);
		if (i != l + 1) cout << l + 2 << ' ' << i << '\n';
	}
	cout << l + 1 << ' ' << r + 1 << '\n';
}

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	sum[0] = a[0]; zcnt[0] = (a[0] == 0);
	for (int i = 1; i < n; ++i) sum[i] = sum[i - 1] + a[i];
	for (int i = 1; i < n; ++i) zcnt[i] = zcnt[i - 1] + (a[i] == 0);
	makecnt[1] = 1;
	for (int i = 2; i <= 18; ++i) {
		makecnt[i] = 1;
		for (int j = 1; j < i; ++j) makecnt[i] += makecnt[j] + 1;
		makecnt[i] -= 1;
	}
	// for (int i = 1; i <= 18; ++i) cout << makecnt[i] << ' ';
	memset(cache, -1, sizeof(cache));
	cout << matchCache(n - 1) << ' ';
	int s = maxgen[n - 1], e = n - 1;
	int cnt = 0;
	while (true) {
		int psum = s == 0 ? sum[e] : sum[e] - sum[s - 1];
		int len = e - s + 1;
		if (psum < len * len) {
			int z = s == 0 ? zcnt[e] : zcnt[e] - zcnt[s - 1];
			cnt += makecnt[len];
			if (z) cnt += 2;
			else ++cnt;
		}
		if (s == 0) break;
		e = s - 1;
		s = maxgen[e];
	}
	cout << cnt << '\n';
	s = maxgen[n - 1], e = n - 1;
	while (true) {
		int psum = s == 0 ? sum[e] : sum[e] - sum[s - 1];
		int len = e - s + 1;
		if (psum < len * len) {
			int z = s == 0 ? zcnt[e] : zcnt[e] - zcnt[s - 1];
			if (z) {
				cout << s + 1 << ' ' << e + 1 << '\n';
				cout << s + 1 << ' ' << e + 1 << '\n';
			}
			else {
				cout << s + 1 << ' ' << e + 1 << '\n';
			}
			generator(s, e);
		}
		if (s == 0) break;
		e = s - 1;
		s = maxgen[e];
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}