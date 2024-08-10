#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1000000007;

ll N;
pair<ll, ll> tree[600000];

void update(int idx, ll val, int node = 1, int s = 0, int e = 200000) {
	if (idx < s || e < idx) return;
	if (s == e) {
		tree[node].second += val;
		tree[node].second %= MOD;
		++tree[node].first;
		return;
	}
	int mid = (s + e) / 2;
	update(idx, val, node * 2, s, mid);
	update(idx, val, node * 2 + 1, mid + 1, e);
	tree[node].second = tree[node * 2].second + tree[node * 2 + 1].second;
	tree[node].second %= MOD;
	tree[node].first = tree[node * 2].first + tree[node * 2 + 1].first;
}

pair<ll, ll> query(int l, int r, int node = 1, int s = 0, int e = 200000) {
	if (l > r) return {0ll, 0ll};
	if (r < s || e < l) return {0ll, 0ll};
	if (l <= s && e <= r) return tree[node];
	int mid = (s + e) / 2;
	pair<ll, ll> lq = query(l, r, node * 2, s, mid);
	pair<ll, ll> rq = query(l, r, node * 2 + 1, mid + 1, e);
	return {lq.first + rq.first, (lq.second + rq.second) % MOD};
}

void solve() {
	cin >> N;
	ll ret = 1ll;
	for (int i = 0; i < N; ++i) {
		ll x; cin >> x;
		update(x, x);
		if (i == 0) continue;
		auto l = query(0, x - 1);
		auto r = query(x + 1, 200000);
		ll tmp = x * l.first;
		tmp %= MOD;
		tmp -= l.second; tmp += MOD; tmp %= MOD;
		tmp += r.second; tmp %= MOD;
		tmp -= (x * r.first) % MOD; tmp += MOD; tmp %= MOD;
		ret *= tmp; ret %= MOD;
	}
	cout << ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}