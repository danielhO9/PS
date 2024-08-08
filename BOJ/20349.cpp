#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int sz = 60;
int n, m, q;
vector<pair<int, ll>> adj[10001];
ll dis[10001];
vector<ll> A;

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
			A.push_back(dis[nv] ^ dis[v] ^ nw);
		}
	}
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
	if (!A.empty()) rref(A);
	for (int i = 0; i < q; ++i) {
		int a, b; cin >> a >> b;
		ll ret = dis[a] ^ dis[b];
		for (auto j: A) if ((ret ^ j) < ret) ret ^= j;
		cout << ret << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}