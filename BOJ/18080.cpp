#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * Description: Fenwick Tree (Binary Indexed Tree) supports point updates and prefix queries.
 * Useful for maintaining cumulative sums efficiently.
 * Time: Both operations are O(\log N).
 */

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
} seg;

ll n, w;
int ord[300001], grp[300001], mn[1000001], mx[1000001], arr[300001];
ll cnt[1000001];
ll ans[1000001];

void _swap(int i, int j) {
    ll x = seg.query(j) - seg.query(i);
    seg.update(i, x);
    seg.update(i + 1, -x);
    seg.update(j, -x);
    seg.update(j + 1, x);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> w;
    for (int i = 1; i <= n; ++i) ord[i] = i;
    for (int i = 1; i <= n; ++i) arr[i] = i;
    for (int i = 1; i <= n; ++i) grp[i] = 1;
    mn[1] = 1, mx[1] = n;
    cnt[1] = n;

    seg = Fenwick {(int) n + 2};
    seg.update(1, w);
    
    for (ll i = w; i >= 1; --i) {
        int k; cin >> k;
        for (int j = 0; j < k; ++j) {
            int c; cin >> c;
            int g = grp[c], o = ord[c];
            if (mn[g] != o) {
                _swap(mn[g], o);
                int u = arr[mn[g]];
                ord[u] = o;
                ord[c] = mn[g];
                
                arr[o] = u;
                arr[mn[g]] = c;
            }
            seg.update(mn[g], -cnt[g + 1] * i);
            seg.update(mn[g] + 1, cnt[g + 1] * i + i);
            seg.update(mx[g] + 1, -i);

            ++cnt[g + 1];
            --cnt[g];

            if (cnt[g + 1] == 1) {
                mn[g + 1] = INT32_MAX;
                mx[g + 1] = INT32_MIN;
            }

            mn[g + 1] = min(mn[g + 1], mn[g]);
            mx[g + 1] = max(mx[g + 1], mn[g]);

            ++mn[g];
            
            ++grp[c];
        }
    }
    cout.precision(7);
    cout << fixed;
    for (int i = 1; i <= n; ++i) ans[arr[i]] = seg.query(i);
    for (int i = 1; i <= n; ++i) cout << (double) ans[i] / w << '\n';
}