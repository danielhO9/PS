#include <bits/stdc++.h>
using namespace std;

int N;
int a[300];
double cache[300 * 301 * 301 + 1];

double matchCache(int x) {
	// cout << x << '\n';
	if (x == 0) return 0.0;
	double& ret = cache[x];
	if (ret > -0.5) return ret;

	int nx = x;

	int cnt[4];
	cnt[3] = x / (301 * 301); x %= (301 * 301);
	cnt[2] = x / 301; x %= 301;
	cnt[1] = x;
	cnt[0] = N - cnt[3] - cnt[2] - cnt[1];
	// for (int i = 0; i < 4; ++i) cout << cnt[i] << ' ';
	// cout << '\n';

	ret = 0.0;
	double p = (double) cnt[0] / N;
	double ex = 0.0;
	for (int i = 1; i <= 3; ++i) if (cnt[i] != 0) {
		int nxt = nx;
		int tmp = 1; for (int j = 0; j < i - 1; ++j) tmp *= 301;
		nxt -= tmp;
		nxt += tmp / 301;
		ex += matchCache(nxt) * cnt[i] / N / (1.0 - p);
	}
	// cout << ex << ' ' << p << '\n';
	ret = ex + 1.0 / (1.0 - p);
	return ret;
	
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> a[i];
	for (int i = 0; i <= 300 * 301 * 301; ++i) cache[i] = -1.0;
	vector<int> cnt(4);
	for (int i = 0; i < N; ++i) ++cnt[a[i]];
	int val = 0;
	int p = 1;
	for (int i = 1; i < 4; ++i) {
		val += p * cnt[i];
		p *= 301;
	}
	cout << fixed;
	cout.precision(10);
	cout << matchCache(val);
}

/*
1 2: 302 -> (4 + 5) / 2
0 2: 301 -> 4
1 1: 2 -> 3
1 0: 1 -> 2
0 0: 0 -> 0
*/