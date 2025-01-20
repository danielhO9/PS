#include <bits/stdc++.h>
using namespace std;

int N;
double p[2999];
double cache[2999][3000];

double matchCache(int i, int j) {
	if (i + 1 < j) return 0.0;
	if (i == 0) {
		if (j == 1) return p[i];
		else return 1.0 - p[i];
	}
	double& ret = cache[i][j];
	if (ret > -0.5) return ret;
	ret = matchCache(i - 1, j) * (1 - p[i]);
	if (j - 1 >= 0) ret += matchCache(i - 1, j - 1) * p[i];
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> p[i];
	for (int i = 0; i < N; ++i) for (int j = 0; j < N + 1; ++j) cache[i][j] = -1.0;
	double ans = 0;
	for (int i = N / 2 + 1; i <= N; ++i) ans += matchCache(N - 1, i);
	cout << fixed;
	cout.precision(10);
	cout << ans;
}