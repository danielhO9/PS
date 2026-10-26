#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	ll x; cin >> x;
	ll val = 1;
	ll ans = 0;
	while (true) {
		++ans;
		val *= ans;
		if (x == val) {
			cout << ans;
			return;
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}