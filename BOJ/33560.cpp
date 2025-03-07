#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N;
ll d[100000];
ll ans[4];
ll ttm, ttmr, s, sr;

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> d[i];
	ttm = 0, ttmr = 4, s = 0, sr = 1;
	for (int j = 0; j < N; ++j) {
		int i = d[j];
		if (ttm > 240) {
			ll val = s - 35;
			if (val >= 0) {
				val /= 30;
				val = min(val, 3ll);
				++ans[val];
			}
			s = 0, ttm = 0;
			ttmr = 4, sr = 1;
		}
		if (i == 1) {
			ll val = s - 35;
			if (val >= 0) {
				val /= 30;
				val = min(val, 3ll);
				++ans[val];
			}
			ttmr = 4, sr = 1;
			s = -sr, ttm = -ttmr;
		} else if (i == 2) {
			if (sr > 1) sr /= 2;
			else if (sr == 1) ttmr += 2;
		} else if (i == 4) {
			ttm += 56;
		} else if (i == 5) {
			if (ttmr > 1) --ttmr;
		} else if (i == 6) {
			if (sr < 32) sr *= 2;
		}
		s += sr;
		ttm += ttmr;
	}
	for (int i = 0; i < 4; ++i) cout << ans[i] << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}