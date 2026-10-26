#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, k;

pair<ll, ll> dnc(ll N) {
	ll ret = 0ll;
	ll cnt = 0ll;
	if (N % 2) {
		ret += (N + 1) / 2;
		++cnt;
		ll nxt = N / 2;
		if (nxt >= k) {
			pair<ll, ll> tmp = dnc(nxt);
			ret += tmp.first * 2ll;
			ret += tmp.second * ((N + 1) / 2);
			cnt += tmp.second * 2ll;
		}
	} else {
		ll nxt = N / 2;
		if (nxt >= k) {
			pair<ll, ll> tmp = dnc(nxt);
			ret += tmp.first * 2ll;
			ret += tmp.second * (N / 2);
			cnt += tmp.second * 2;
		}
	}
	return make_pair(ret, cnt);
}

void solve() {
	cin >> n >> k;
	cout << dnc(n).first << '\n';
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	while (t--)
		solve();
}