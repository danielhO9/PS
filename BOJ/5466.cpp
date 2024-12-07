#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 500003;

struct segtree {
	using elem = ll;
	int n;
	elem T[2 * N];
	inline elem agg(elem a, elem b) { return max(a, b); }
	void build() {
		n = N;
		for (int i = 0; i < n; i++)
			T[n + i] = INT32_MIN;
		for (int i = n - 1; i > 0; i--)
			T[i] = agg(T[i << 1], T[(i << 1) | 1]);
	}
	void modify(int pos, elem val) {
		for (T[pos += n] = val; pos > 1; pos >>= 1)
			T[pos >> 1] = agg(T[pos], T[pos ^ 1]);
	}
	// query i s on [ l , r ) ! !
	elem query(int l, int r) {
		elem res = INT32_MIN;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1)
				res = agg(T[l++], res);
			if (r & 1)
				res = agg(res, T[--r]);
		}
		return res;
	}
};

ll n, U, D, S;
ll Tk[N], Lk[N], Mk[N];
vector<int> pos[N];
segtree segd;
segtree segu;

void solve() {
	cin >> n >> U >> D >> S;
	for (int i = 0; i < n; ++i) cin >> Tk[i] >> Lk[i] >> Mk[i];
	segd.build();
	segu.build();
	for (int i = 0; i < n; ++i) pos[Tk[i]].push_back(i);
	for (int i = 0; i < N; ++i) if (!pos[i].empty()) {
		sort(pos[i].begin(), pos[i].end(), [](const int a, const int b) {
			return Lk[a] < Lk[b];
		});
	}
	segu.modify(S, -S * U);
	segd.modify(S, S * D);
	vector<ll> his;
	vector<ll> upd;
	for (int i = 1; i < N - 1; ++i) {
		if (pos[i].empty()) continue;
		his.clear();
		upd.clear();
		for (auto j: pos[i]) {
			ll val = INT32_MIN;
			val = max(val, segd.query(1, Lk[j]) - D * Lk[j]);
			val = max(val, segu.query(Lk[j] + 1, N) + U * Lk[j]);
			val += Mk[j];
			his.push_back(val);
			upd.push_back(val);
		}
		ll prv = his.front();
		for (int j = 1; j < his.size(); ++j) {
			ll val = max(prv - D * (Lk[pos[i][j]] - Lk[pos[i][j - 1]]) + Mk[pos[i][j]], his[j]);
			prv = val;
			upd[j] = max(upd[j], val);
		}
		prv = his.back();
		for (int j = (int)his.size() - 2; j >= 0; --j) {
			ll val = max(prv - U * (Lk[pos[i][j + 1]] - Lk[pos[i][j]]) + Mk[pos[i][j]], his[j]);
			prv = val;
			upd[j] = max(upd[j], val);
		}
		assert(his.size() == upd.size());
		for (int j = 0; j < his.size(); ++j) {
			segu.modify(Lk[pos[i][j]], upd[j] - U * Lk[pos[i][j]]);
			segd.modify(Lk[pos[i][j]], upd[j] + D * Lk[pos[i][j]]);
		}
	}
	ll ans = INT32_MIN;
	ans = max(ans, segd.query(1, S + 1) - D * S);
	ans = max(ans, segu.query(S, N) + U * S);
	assert(ans >= 0);
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}