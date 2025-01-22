#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
ll a[16][16];
ll cache[1 << 16];
ll cost[1 << 16];

ll matchCache(int mask) {
	if (mask == 0) return 0;
	ll& ret = cache[mask];
	if (ret != -1) return ret;
	ret = LLONG_MIN;
	vector<int> digits;
	for (int i = 0; i < N; ++i) if ((mask >> i) & 1) digits.push_back(i);
	int sz = digits.size();
	for (int i = 1; i < (1 << sz); ++i) {
		int nmask = mask;
		int group = 0;
		for (int j = 0; j < sz; ++j) if ((i >> j) & 1) {
			nmask ^= (1 << digits[j]);
			group ^= (1 << digits[j]);
		}
		ret = max(ret, matchCache(nmask) + cost[group]);
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> a[i][j];
	memset(cache, -1, sizeof(cache));
	for (int i = 0; i < (1 << N); ++i) {
		for (int j = 0; j < N; ++j) for (int k = j + 1; k < N; ++k) if (((i >> j) & 1) && ((i >> k) & 1)) {
			cost[i] += a[j][k];
		}
	}
	cout << matchCache((1 << N) - 1);

}