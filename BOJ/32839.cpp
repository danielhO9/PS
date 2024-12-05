#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_N = 3e6 + 1;

struct segtree {
	using elem = ll;
	int n;
	elem T[2 * MAX_N];
	inline elem agg(elem a, elem b) { return min(a, b); }
	void build(vector<elem> &v) {
		for (auto& i: T) i = LLONG_MAX;
		n = v.size();
	}
	void modify(int pos, elem val) {
		for (T[pos += n] = val; pos > 1; pos >>= 1)
			T[pos >> 1] = agg(T[pos], T[pos ^ 1]);
	}
	// query i s on [ l , r ) ! !
	elem query(int l, int r) {
		elem res = LLONG_MAX;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1)
				res = agg(T[l++], res);
			if (r & 1)
				res = agg(res, T[--r]);
		}
		return res;
	}
} seg;

int cor[26];

void solve() {
	memset(cor, -1, sizeof(cor));
	string s;
	cin >> s;
	vector<ll> arr(s.size(), 0);
	seg.build(arr);

	ll ans = 0ll;
	for (int i = (int)s.size() - 1; i >= 0; --i) {
		ll nval;
		if (cor[s[i] - 'a'] == -1) nval = -1;
		else nval = seg.query(i + 1, cor[s[i] - 'a'] + 1);
		++nval;
		seg.modify(i, nval);
		ans = max(ans, nval);
		cor[s[i] - 'a'] = i;
	}
	cout << ans + 1;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	solve();
}