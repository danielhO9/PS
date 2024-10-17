#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
const int N = 100000;

struct segtree {
	using elem = ll;
	int n;
	elem T[2 * N];

	inline elem agg(elem a, elem b) {
		return max(a, b);
	}

	void build(vector<elem>& v) {
		n = v.size();
		for (int i = 0; i < n; ++i) {
			T[n + i] = v[i];
		}
		for (int i = n - 1; i > 0; --i) {
			T[i] = agg(T[i << 1], T[(i << 1) | 1]);
		}
	}

	void modify(int pos, elem val) {
		for (T[pos += n] = val; pos > 1; pos >>= 1) {
			T[pos >> 1] = agg(T[pos], T[pos ^ 1]);
		}
	}
	elem query(int l, int r) {
		elem res = 0;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) res = agg(T[l++], res);
			if (r & 1) res = agg(res, T[--r]);
		}
		return res;
	}
} seg;

ll n, r, w, h;
vector<pll> cor;
unordered_map<ll, ll> m;

void solve() {
	cin >> n >> r >> w >> h;
	for (int i = 0; i < n; ++i) {
		ll x, y; cin >> x >> y;
		cor.push_back({y - x * r, y + x * r});
	}
	sort(cor.begin(), cor.end(), [](pll& a, pll& b) {
		if (a.first == b.first) return a.second > b.second;
		return a.first > b.first;
	});
	set<ll> s;
	for (int i = 0; i < n; ++i) s.insert(cor[i].second);
	int idx = 0;
	for (auto i: s) m[i] = idx++;
	const int mx = s.size() + 1;
	vector<ll> v(mx);
	seg.build(v);
	ll ans = 0ll;
	for (int i = 0; i < n; ++i) {
		int idx = m[cor[i].second];
		ll val = seg.query(idx, mx);
		ans = max(ans, val + 1);
		seg.modify(idx, val + 1);
	}
	cout << ans;
	
}

int32_t main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}