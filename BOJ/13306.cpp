#include <bits/stdc++.h>
using namespace std;

// 0-index
struct UF {
	vector<int> par, rk;

	UF(int _sz) {
		par.resize(_sz);
		rk.resize(_sz);
		for (int i = 0; i < _sz; ++i) par[i] = i;
	}
	int find(int x) {
		if (par[x] == x) return x;
		par[x] = find(par[x]);
		return par[x];
	}
	void union_rank(int x, int y) {
		x = find(x); y = find(y);
		if (x == y) return;
		if (rk[x] > rk[y]) swap(x, y);
		par[x] = y;
		if (rk[x] == rk[y]) ++rk[y];
	}
};

struct Query {
    int x, a, b;
};

int N, Q;
int par[200001];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> Q;
    for (int i = 2; i <= N; ++i) cin >> par[i];
    vector<Query> v;
    for (int i = 0; i < N - 1 + Q; ++i) {
        int x; cin >> x;
        if (x == 0) {
            int b; cin >> b;
            v.push_back(Query {x, b, par[b]});
        } else {
            int c, d; cin >> c >> d;
            v.push_back(Query {x, c, d});
        }
    }
    UF uf {N + 1};
    reverse(v.begin(), v.end());
    vector<int> ans;
    for (Query& q: v) {
        if (q.x == 0) uf.union_rank(q.a, q.b);
        else {
            if (uf.find(q.a) == uf.find(q.b)) ans.push_back(1);
            else ans.push_back(0);
        }
    }
    reverse(ans.begin(), ans.end());
    for (auto i: ans) {
        if (i) cout << "YES\n";
        else cout << "NO\n";
    }
}