#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// returns {gcd, x, y}
tuple<ll, ll, ll> extended_euclidean(ll a, ll b) {
    if (b == 0)
        return {a, 1, 0};
    auto [g, x, y] = extended_euclidean(b, a%b);
    return {g, y, x-(a/b)*y};
}

ll n, a, b;
ll c[100000];

void solve() {
	cin >> n >> a >> b;
	for (int i = 0; i < n; ++i) cin >> c[i];
	if (n == 1) {
		cout << 0 << '\n';
		return;
	}
	ll g = get<0>(extended_euclidean(a, b));
	ll lcd = a * b / g;
	for (int i = 0; i < n; ++i) {
		c[i] %= lcd;
		ll tmp = c[i] / g;
		c[i] -= tmp * g;
	}
	deque<ll> dq;
	for (int i = 0; i < n; ++i) dq.push_back(c[i]);
	sort(dq.begin(), dq.end());
	ll ans = dq.back() - dq.front();
	for (int i = 0; i < n; ++i) {
		ll last = dq.back(); dq.pop_back();
		dq.push_front(last - g);
		ans = min(ans, dq.back() - dq.front());
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}