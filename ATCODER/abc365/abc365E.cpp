#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
ll A[200001];
ll val[200001];
ll cnt[200001];
ll ans = 0;

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> A[i];
	for (int i = 0; i < 30; ++i) {
		for (int j = 0; j < N; ++j) val[j] = ((A[j] >> i) & 1);
		for (int j = 1; j < N; ++j) {
			val[j] += val[j - 1];
			val[j] %= 2;
		}
		for (int j = 0; j < N; ++j) {
			if (j == 0) cnt[j] = val[j];
			else cnt[j] = cnt[j - 1] + val[j];
		}
		ll tans = 0ll;
		for (int j = 1; j < N; ++j) {
			if (j == 1) {
				if (val[1]) ++tans;
				continue;
			}
			if (val[j] == 1) {
				tans += (j - 1) - cnt[j - 2] + 1;
			} else {
				tans += cnt[j - 2];
			}
		}
		ans += tans * (1ll << i);
		// cout << ans << ' ';
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}