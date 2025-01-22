#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAX = 1e13;

int N;
ll a[3000];
ll cache[3000][3000];

ll matchCache(int l, int r) {
	if (l == r) {
		if (N % 2 == 1) return a[l];
		else return -a[l];
	}
	ll& ret = cache[l][r];
	if (ret != MAX) return ret;
	int len = r - l + 1;
	if (len % 2 == N % 2) {
		ret = LLONG_MIN;
		ret = max(matchCache(l + 1, r) + a[l], matchCache(l, r - 1) + a[r]);

	} else {
		ret = LLONG_MAX;
		ret = min(matchCache(l + 1, r) - a[l], matchCache(l, r - 1) - a[r]);
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> a[i];
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cache[i][j] = MAX;
	cout << matchCache(0, N - 1);
}