#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Fenwick {
    vector<ll> tree;

    Fenwick() = default;
    Fenwick(int sz) { tree.resize(sz); }
    void update(int i, ll dif) { while (i < tree.size()) { tree[i] += dif; i += (i & -i); } }
    void update_range(int i, int j, ll dif) {
        update(i, dif);
        if (j + 1 < tree.size()) update(j + 1, -dif);
    }
    ll query(int i) {
        ll ret = 0;
        while (i > 0) { ret += tree[i]; i -= (i & -i); }
        return ret;
    }
} seg;

struct Query {
    int l, r; ll a;
};

int N, M, Q;
vector<int> areas[300001];
ll p[300001];
int l[300001], r[300001];
vector<Query> query;
vector<vector<int>> arr;
ll cnt[300001];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;
    for (int i = 1; i <= M; ++i) {
        int o; cin >> o;
        areas[o].push_back(i);
    }
    for (int i = 1; i <= N; ++i) cin >> p[i];
    cin >> Q; query.resize(Q);
    for (int i = 0; i < Q; ++i) cin >> query[i].l >> query[i].r >> query[i].a;
    seg = Fenwick {M + 1};
    for (int i = 0; i < Q; ++i) {
        if (query[i].l <= query[i].r) seg.update_range(query[i].l, query[i].r, query[i].a);
        else {
            seg.update_range(query[i].l, M, query[i].a);
            seg.update_range(1, query[i].r, query[i].a);
        }
    }
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= N; ++i) for (int j: areas[i]) cnt[i] = min(cnt[i] + seg.query(j), p[i]);
    arr.resize(Q);
    for (int i = 1; i <= N; ++i) {
        l[i] = -1;
        if (cnt[i] < p[i]) r[i] = -1;
        else r[i] = Q - 1;
        if (l[i] + 1 < r[i]) {
            int mid = (l[i] + r[i]) / 2;
            arr[mid].push_back(i);
        }
    }
    while (true) {
        bool flag = true;
        for (int i = 0; i < Q; ++i) if (!arr[i].empty()) flag = false;
        if (flag) break;
        vector<vector<int>> narr(Q);
        seg = Fenwick {M + 1};
        for (int i = 0; i < Q; ++i) {
            if (query[i].l <= query[i].r) seg.update_range(query[i].l, query[i].r, query[i].a);
            else {
                seg.update_range(query[i].l, M, query[i].a);
                seg.update_range(1, query[i].r, query[i].a);
            }
            for (int j: arr[i]) {
                cnt[j] = 0;
                for (int k: areas[j]) cnt[j] = min(seg.query(k) + cnt[j], p[j]);
                if (cnt[j] < p[j]) l[j] = i;
                else r[j] = i;

                if (l[j] + 1 < r[j]) {
                    int mid = (l[j] + r[j]) / 2;
                    narr[mid].push_back(j);
                }
            }
        }
        swap(narr, arr);
    }
    for (int i = 1; i <= N; ++i) {
        if (r[i] == -1) cout << "NIE\n";
        else cout << r[i] + 1 << '\n';
    }
}