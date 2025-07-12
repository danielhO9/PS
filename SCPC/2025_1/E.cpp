#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int par[100001];
int sz[100001];

int find(int x) {
    if (par[x] == x) return x;
    par[x] = find(par[x]);
    return par[x];
}

void merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;
    if (sz[x] < sz[y]) swap(x, y);
    par[y] = x;
    sz[x] += sz[y];
}

int N, M;

struct Edge {
    ll d; int s, e;

    bool operator<(const Edge& a) const { return d > a.d; }
};

void init() {
    for (int i = 1; i <= N; ++i) par[i] = i;
    for (int i = 1; i <= N; ++i) sz[i] = 1;
}


void solve() {
    cin >> N >> M;
    vector<Edge> edges(M);
    priority_queue<Edge> pq;
    ll mx = 0, mn = LLONG_MAX;
    for (int i = 0; i < M; ++i) {
        cin >> edges[i].s >> edges[i].e >> edges[i].d;
        mx = max(mx, edges[i].d);
        mn = min(mn, edges[i].d);
        pq.push(edges[i]);
    }
    vector<Edge> tree;
    vector<Edge> medges;
    init();
    ll sm = 0;
    bool flag = false;
    while (!pq.empty()) {
        auto e = pq.top(); pq.pop();
        if (e.d == mx) medges.push_back(e);
        if (find(e.s) == find(e.e)) continue;
        if (e.d == mx) flag = true;
        tree.push_back(e);
        sm += e.d;
        merge(e.s, e.e);
    }
    if (flag) {
        ll dif = mx - mn;
        cout << dif << ' ' << sm << '\n';
        return;
    }
    if (N == 2) {
        cout << 0 << ' ' << sm << '\n';
        return;
    }
    
    int sz = medges.size();
    vector<int> l(sz, -1), r(sz, N - 2);
    vector<int> midx[N];
    while (true) {
        flag = true;
        for (int i = 0; i < sz; ++i) if (l[i] + 1 < r[i]) {
            flag = false;
            int mid = (l[i] + r[i]) / 2;
            midx[mid].push_back(i);
        }
        if (flag) break;
        init();
        for (int i = 0; i < N; ++i) {
            auto edge = tree[i];
            merge(edge.s, edge.e);
            for (int j: midx[i]) {
                auto cedge = medges[j];
                if (find(cedge.s) == find(cedge.e)) r[j] = i;
                else l[j] = i;
            }
            midx[i].clear();
        }
    }
    
    int b = -1;
    for (int i = 0; i < sz; ++i) b = max(b, r[i]);
    assert(b != -1);

    ll nmn = LLONG_MAX;
    for (int i = 0; i < N - 1; ++i) if (i != b) nmn = min(nmn, tree[i].d);
    nmn = min(nmn, mx);
    ll dif1 = mx - nmn;
    ll sm1 = sm - tree[b].d + mx;
    if (b != 0 || tree[1].d == tree[0].d) {
        cout << dif1 << ' ' << sm1 << '\n';
        return;
    }
    
    init();
    merge(tree[0].s, tree[0].e);
    medges.clear();
    mx = 0;
    for (int i = 0; i < M; ++i) if (find(edges[i].s) != find(edges[i].e)) mx = max(mx, edges[i].d);
    
    flag = false;
    for (int i = 0; i < N - 1; ++i) if (tree[i].d == mx) flag = true;
    if (flag) {
        cout << mx - tree[0].d << ' ' << sm << '\n';
        return;
    }

    for (int i = 0; i < M; ++i) if (edges[i].d == mx) medges.push_back(edges[i]);
    
    sz = medges.size();
    l = vector<int>(sz, -1);
    r = vector<int>(sz, N - 2);
    while (true) {
        flag = true;
        for (int i = 0; i < sz; ++i) if (l[i] + 1 < r[i]) {
            flag = false;
            int mid = (l[i] + r[i]) / 2;
            midx[mid].push_back(i);
        }
        if (flag) break;
        init();
        for (int i = 0; i < N; ++i) {
            auto edge = tree[i];
            merge(edge.s, edge.e);
            for (int j: midx[i]) {
                auto cedge = medges[j];
                if (find(cedge.s) == find(cedge.e)) r[j] = i;
                else l[j] = i;
            }
            midx[i].clear();
        }
    }
    
    b = -1;
    for (int i = 0; i < sz; ++i) b = max(b, r[i]);
    ll dif2 = mx - tree[0].d;
    ll sm2 = sm - tree[b].d + mx;
    if (dif1 < dif2 || (dif1 == dif2 && sm1 > sm2)) cout << dif2 << ' ' << sm2 << '\n';
    else cout << dif1 << ' ' << sm1 << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << '\n';
        solve();
    }
}