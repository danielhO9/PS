#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, Q;
ll V[500000];
ll psm[500000];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> Q;
    for (int i = 0; i < N; ++i) cin >> V[i];
    psm[0] = V[0];
    for (int i = 1; i < N; ++i) psm[i] = psm[i - 1] + V[i];
    vector<pair<ll, int>> v;
    for (int i = 0; i < N; ++i) {
        pair<ll, int> cur = make_pair(V[i] + i, i);
        if (!v.empty() && v.back().first >= cur.first) continue;
        v.push_back(cur);
    }
    int idx = 1;
    ll sm = 0;
    ll h = V[0];
    while (Q--) {
        int t; cin >> t;
        if (t == 1) {
            ll x; cin >> x; sm += x;
            while (idx < v.size()) {
                ll nxt_amount = (2ll * v[idx].first - v[idx].second + 1) * v[idx].second / 2;
                ll cur_amount = sm + psm[v[idx].second - 1];
                if (nxt_amount <= cur_amount) {
                    h = v[idx].first;
                    ++idx;
                } else break;
            }
        } else {
            ll len = idx == v.size() ? N : v[idx].second;
            ll mn = (2 * h - len + 1) * len / 2;
            ll amount = psm[len - 1] + sm;
            if (mn > amount) cout << h << '\n';
            else cout << h + (amount - mn) / len << '\n';
        }
    }
}