#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int Q; cin >> Q;
	deque<ll> v;
	ll sum = 0;
	ll dif = 0;
	while (Q--) {
		int t; cin >> t;
		if (t == 1) {
			ll l; cin >> l;
			sum += l;
			v.push_back(sum);

		} else if (t == 2) {
			dif = v[0];
			v.pop_front();
		} else {
			ll k; cin >> k;
			if (k >= 2) cout << v[k - 2] - dif << '\n';
			else cout << 0 << '\n';
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}