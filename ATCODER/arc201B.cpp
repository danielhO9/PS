#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, W;
ll X[200000], Y[200000];
bool vis[200000];
vector<int> v[60];

// 0-index
struct UF {
	vector<int> par, sz;

	void init(int _sz) {
		par.resize(_sz);
		sz.resize(_sz);
		for (int i = 0; i < _sz; ++i) par[i] = i;
		for (int i = 0; i < _sz; ++i) sz[i] = 1;
	}

	int find(int x) {
		if (par[x] == x) return x;
		par[x] = find(par[x]);
		return par[x];
	}

	void union_path(int x, int y) {
		x = find(x); y = find(y);
		if (x == y) return;
		if (sz[x] > sz[y]) swap(x, y);
		par[x] = y;
		sz[y] += sz[x];
	}
};

void solve() {
    cin >> N >> W;
    for (int i = 0; i < N; ++i) vis[i] = false;
    for (int i = 0; i < N; ++i) cin >> X[i] >> Y[i];
    ll ans = 0;
    UF uf;
    for (int i = 0; i < 60; ++i) if ((W >> i) & 1) {
        priority_queue<pair<ll, int>> pq, npq;
        uf.init(N);
        for (int j = 0; j <= i; ++j) v[j].clear();
        for (int j = 0; j < N; ++j) if (!vis[j]) v[X[j]].push_back(j);
        for (int j = 0; j <= i; ++j) {
            while (!npq.empty()) npq.pop();
            while (pq.size() >= 2) {
                auto a = pq.top(); pq.pop();
                auto b = pq.top(); pq.pop();
                uf.union_path(a.second, b.second);
                npq.push(make_pair(a.first + b.first, a.second));
            }
            if (!pq.empty()) {
                auto a = pq.top(); pq.pop();
                npq.push(make_pair(a.first, a.second));
            }
            for (auto k: v[j]) npq.push(make_pair(Y[k], k));
            swap(npq, pq);
        }
        if (!pq.empty()) {
            auto res = pq.top();
            ans += res.first;
            res.second = uf.find(res.second);
            for (int j = 0; j < N; ++j) if (uf.find(j) == res.second) vis[j] = true;   
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}