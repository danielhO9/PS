#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int sz = 30;
int n, m, q;
vector<pair<int, ll>> adj[100001];
ll dis[100001];
vector<ll> basis;
ll sumdis[100001];
ll cnt[60][100001];

void rref(vector<ll>& A) {
	if (A.empty()) return;
    int m = A.size();
    for (int j = sz - 1, r = 0; j >= 0 && r < m; --j) {
        for (int i = r; i < m; i++) {
            if ((A[i] >> j) & 1) {
                swap(A[r], A[i]);
                break;
            }
        }
        if ((A[r] >> j) & 1) {
            for (int i = 0; i < m; i++) if (i != r) {
                if ((A[i] >> j) & 1) {
                    A[i] ^= A[r];
                }
            }
            ++r;
        }
    }
	while (A.back() == 0ll) A.pop_back();
}

void dfs(int v, int p, ll w) {
	if (v == 1) dis[v] = 0ll;
	else {
		dis[v] = dis[p] ^ w;
	}
	for (auto [nv, nw]: adj[v]) if (nv != p) {
		if (dis[nv] == -1) dfs(nv, v, nw);
		else {
			basis.push_back(dis[nv] ^ dis[v] ^ nw);
		}
	}
}

ll calc(ll x) {
	if (x < 2) return 0ll;
	ll tmp = x * (x - 1) / 2;
	return tmp % 2;
}

void solve() {
	cin >> n >> m >> q;
	for (int i = 0; i < m; ++i) {
		int x, y; ll w; cin >> x >> y >> w;
		adj[x].push_back({y, w});
		adj[y].push_back({x, w});
	}
	memset(dis, -1, sizeof(dis));
	dfs(1, 0, 0ll);
	for (int i = 1; i <= n; ++i) sumdis[i] = sumdis[i - 1] ^ dis[i];
	if (!basis.empty()) rref(basis);

	for (int i = 0; i < basis.size(); ++i) {
		for (int j = 1; j <= n; ++j) {
			if ((basis[i] ^ dis[j]) > dis[j]) cnt[i][j] = 1;
			else cnt[i][j] = 0;
		}
	}
	for (int i = 0; i < basis.size(); ++i) {
		for (int j = 1; j <= n; ++j) cnt[i][j] += cnt[i][j - 1];
	}

	for (int i = 0; i < q; ++i) {
		int a, b; cin >> a >> b;
		ll len = b - a + 1;
		ll ret = 0;
		if (len % 2 == 0) ret = sumdis[b] ^ sumdis[a - 1];
		for (int i = 0; i < basis.size(); ++i) {
			ll tmp = cnt[i][b] - cnt[i][a - 1];
			if (calc(tmp) + calc(len - tmp) == 1) ret ^= basis[i];	
		}
		cout << ret << '\n';
	}

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}