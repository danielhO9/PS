#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 1-index
struct Fenwick {
    vector<ll> tree;

    Fenwick() = default;
    Fenwick(int sz) { tree.resize(sz); }
    void update(int i, ll dif) { while (i < tree.size()) { tree[i] += dif; i += (i & -i); } }
    ll query(int i) {
        ll ret = 0;
        while (i > 0) { ret += tree[i]; i -= (i & -i); }
        return ret;
    }
};

// 1-index
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