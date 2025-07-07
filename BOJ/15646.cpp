#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Fenwick2D {
    int n, m;
    vector<vector<ll>> tree;

    Fenwick2D(int n, int m): n(n), m(m) { 
        tree.resize(n);
        for (int i = 0; i < n; ++i) tree[i].resize(m);
    }
    void update(int y, int x, ll dif) {
        for (int i = y; i < n; i += (i & -i))
            for (int j = x; j < m; j += (j & -j)) tree[i][j] += dif;
    }
    ll query(int y, int x) {
        ll ret = 0;
        for (int i = y; i; i -= (i & -i))
            for (int j = x; j; j -= (j & -j)) ret += tree[i][j];
        return ret;
    }
};

int N, M, Q;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M >> Q;
    Fenwick2D tree {N + 2, M + 2};
    while (Q--) {
        int t; cin >> t;
        if (t == 1) {
            int x1, y1, x2, y2; ll d; cin >> x1 >> y1 >> x2 >> y2 >> d;
            tree.update(x2+1, y2+1, d);
            tree.update(x1, y2+1, -d);
            tree.update(x2+1, y1, -d);
            tree.update(x1, y1, d);
        } else {
            int x, y; cin >> x >> y;
            cout << tree.query(x, y) << '\n';
        }
    }
}