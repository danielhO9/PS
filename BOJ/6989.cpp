#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
ll score[150];
ll K;
bitset<1200000> cache[150];
ll seg[150][150];

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> score[i];
	cin >> K;
	if (K >= 1200000) {
		cout << K;
		return;
	}
	for (int i = 0; i < N; ++i) for (int j = i; j < N; ++j) {
		ll ret = 0ll, tmp = 1ll;
		for (int k = j; k >= i; --k) {
			ret += tmp * score[k];
			++tmp;
		}
		seg[i][j] = ret;
	}
	cache[0][0] = 1;
	cache[0][score[0]] = 1;
	for (int i = 1; i < N; ++i) {
		cache[i] = cache[i - 1];
		for (int j = 0; j <= i; ++j) {
			if (j >= 2) cache[i] |= (cache[j - 2] << (seg[j][i]));
			else cache[i][seg[j][i]] = 1;
		}
	}
	ll ans = K;
	while (cache[N - 1][ans]) ++ans;
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}