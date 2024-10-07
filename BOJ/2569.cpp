#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N;
bool vis[10000];
ll w[10000];
ll nxt[10000];
ll ans = 0;

void solve() {
	cin >> N;
	for (ll i = 0; i < N; ++i) cin >> w[i];
	ll mn = *min_element(w, w + N);
	vector<pair<ll, ll>> v;
	for (ll i = 0; i < N; ++i) {
		v.push_back({w[i], i});
	}
	sort(v.begin(), v.end());
	for (ll i = 0; i < N; ++i) {
		nxt[v[i].second] = i;
	}
	// for (int i = 0; i < N; ++i) cout << nxt[i] << ' ';
	for (ll i = 0; i < N; ++i) {
		ll c = 0;
		ll sm = 0;
		ll now = i;
		ll pmn = LLONG_MAX;
		while (!vis[now]) {
			vis[now] = true;
			sm += w[now];
			pmn = min(pmn, w[now]);
			now = nxt[now];
			++c;
		}
		if (c == 0) continue;
		ans += min((c - 1) * pmn + sm - pmn, c * mn + sm + pmn + mn);
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}