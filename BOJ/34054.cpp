#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Seg {
    ll l, r, t, idx;
};

ll N, Q;
ll l[250000], r[250000], s[250000], e[250000], ans[250000];
const ll MAX = 1000000;

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

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> Q;
    for (int i = 0; i < N; ++i) cin >> l[i] >> r[i];
    for (int i = 0; i < Q; ++i) cin >> s[i] >> e[i];
    vector<Seg> v;
    for (int i = 0; i < N; ++i) v.push_back(Seg {l[i], r[i], 0, i});
    for (int i = 0; i < Q; ++i) v.push_back(Seg {s[i], e[i], 1, i});
    sort(v.begin(), v.end(), [](const Seg& a, const Seg& b) {
        if (a.l + a.r == b.l + b.r) return a.t < b.t;
        return a.l + a.r < b.l + b.r;
    });
    Fenwick a = Fenwick {1000001}, b = Fenwick {1000001};
    for (auto seg: v) {
        if (seg.t == 0) {
            a.update(seg.r, seg.l - seg.r);
            b.update(seg.r, seg.r * (seg.r - seg.l));
        } else {
            ans[seg.idx] += (a.query(MAX) - a.query(seg.l)) * seg.l + b.query(MAX) - b.query(seg.l);
        }
    }
    sort(v.begin(), v.end(), [](const Seg& a, const Seg& b) {
        if (a.l + a.r == b.l + b.r) return a.t > b.t;
        return a.l + a.r > b.l + b.r;
    });
    a = Fenwick {1000001}, b = Fenwick {1000001};
    for (auto seg: v) {
        if (seg.t == 0) {
            a.update(seg.l, seg.r - seg.l);
            b.update(seg.l, seg.l * (seg.l - seg.r));
        } else {
            ans[seg.idx] += a.query(seg.r) * seg.r + b.query(seg.r);
        }
    }
    for (int i = 0; i < Q; ++i) cout << ans[i] * 2 << '\n';
}