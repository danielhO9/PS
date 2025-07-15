#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
    ll a, b, x;
};

int N;
ll a[1000000], b[1000000], x[1000000];

// 1-index
struct Fenwick {
    vector<ll> tree;

    Fenwick() = default;
    Fenwick(int sz) { tree.resize(sz); for (int i = 0; i < sz; ++i) tree[i] = LLONG_MIN; }
    void update(int i, ll dif) { while (i < tree.size()) { tree[i] = max(tree[i], dif); i += (i & -i); } }
    ll query(int i) {
        ll ret = LLONG_MIN;
        while (i > 0) { ret = max(ret, tree[i]); i -= (i & -i); }
        return ret;
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> a[i] >> b[i] >> x[i];
    for (int i = 1; i < N; ++i) {
        a[i] += a[i - 1];
        b[i] += b[i - 1];
    }
    vector<ll> sa, sb;
    sa.push_back(0); sb.push_back(0);
    for (int i = 0; i < N; ++i) {
        sa.push_back(a[i]);
        sb.push_back(b[i]);
    }
    sort(sa.begin(), sa.end());
    sa.erase(unique(sa.begin(), sa.end()), sa.end());
    sort(sb.begin(), sb.end());
    sb.erase(unique(sb.begin(), sb.end()), sb.end());
    vector<Point> v;
    v.push_back(Point{lower_bound(sa.begin(), sa.end(), 0) - sa.begin(), lower_bound(sb.begin(), sb.end(), 0) - sb.begin(), 0});
    for (int i = 0; i < N; ++i) v.push_back(Point{lower_bound(sa.begin(), sa.end(), a[i]) - sa.begin(), lower_bound(sb.begin(), sb.end(), b[i]) - sb.begin(), x[i]});
    Fenwick seg = Fenwick {(int)sb.size() + 1};
    sort(v.begin(), v.end(), [](const Point& a, const Point& b) {
        if (a.a == b.a && a.b == b.b) return a.x < b.x;
        if (a.a == b.a) return a.b < b.b;
        return a.a > b.a;
    });

    ll ans = 0;
    bool flag = false;
    
    for (auto pt: v) {
        if (!flag && pt.x != 0) continue;
        if (pt.x == 0) flag = true;

        auto tmp = seg.query(pt.b + 1);
        if (pt.x == 0) seg.update(pt.b + 1, 0);
        else if (tmp != LLONG_MIN) {
            ans = max(ans, tmp + pt.x);
            seg.update(pt.b + 1, tmp + pt.x);
        }
    }
    cout << ans;
}