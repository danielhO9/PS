#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	LL a, b, r; cin >> a >> b >> r;
	LL ret = LLONG_MAX;
	LL x = 0, ans = 0;
	bool first = 1;
	for (LL i = 59; i >= 0; --i) {
		if (((a >> i) & 1LL) != ((b >> i) & 1LL)) {
			if (((a >> i) & 1LL)) {
				if (first) {
					first = 0;
					ans += 1LL << i;
				} else {
					if (x + (1LL << i) <= r) {
						ans -= 1LL << i;
						x += 1LL << i;
					} else {
						ans += 1LL << i;
					}
				}
			} else {
				if (first) {
					first = 0;
					if (x + (1LL << i) <= r) {
						ans += 1LL << i;
						x += 1LL << i;
					} else {
						ans -= 1LL << i;
					}
				} else {
					ans -= 1LL << i;
				}
			}
		}
	}
	ret = min(ret, abs(ans));
	x = 0, ans = 0;
	first = 1;
	swap(a, b);
	for (LL i = 59; i >= 0; --i) {
		if (((a >> i) & 1LL) != ((b >> i) & 1LL)) {
			if (((a >> i) & 1LL)) {
				if (first) {
					first = 0;
					ans += 1LL << i;
				} else {
					if (x + (1LL << i) <= r) {
						ans -= 1LL << i;
						x += 1LL << i;
					} else {
						ans += 1LL << i;
					}
				}
			} else {
				if (first) {
					first = 0;
					if (x + (1LL << i) <= r) {
						ans += 1LL << i;
						x += 1LL << i;
					} else {
						ans -= 1LL << i;
					}
				} else {
					ans -= 1LL << i;
				}
			}
		}
	}
	ret = min(ret, abs(ans));
	cout << ret << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}