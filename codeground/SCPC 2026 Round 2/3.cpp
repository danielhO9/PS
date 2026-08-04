#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, m;
ll arr1[15000], arr2[15000];
vector<vector<ll>> v;

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> arr1[i];
    for (int i = 0; i < m; ++i) cin >> arr2[i];

    vector<pair<ll, bool>> tmp;
    for (int i = 0; i < n; ++i) tmp.push_back(make_pair(arr1[i], 0));
    for (int i = 0; i < m; ++i) tmp.push_back(make_pair(arr2[i], 1));
    sort(tmp.begin(),tmp.end());

    for (auto& i: v) i.clear();
    v.clear();
    for (int i = 0; i < n + m; ++i) {
        if (i == 0) v.push_back({tmp[i].first});
        else if (tmp[i].second != tmp[i - 1].second) v.push_back({tmp[i].first});
        else v.back().push_back(tmp[i].first);
    }

    vector<ll> prv(v[0].size(), 0);
    for (int t = 1; t < v.size(); ++t) {
        
        vector<vector<ll>> cache(v[t - 1].size(), vector<ll>(v[t].size()));
        for (int i = (int) v[t - 1].size() - 1; i >= 0; --i) {
            for (int j = 0; j < v[t].size(); ++j) {
                cache[i][j] = LLONG_MAX;
                if (i + 1 < v[t - 1].size()) cache[i][j] = min(cache[i + 1][j], cache[i][j]);
                if (j - 1 >= 0) cache[i][j] = min(cache[i][j - 1], cache[i][j]);
                if (cache[i][j] == LLONG_MAX) cache[i][j] = 0;
                cache[i][j] += v[t][j] - v[t - 1][i];
                // cout << cache[i][j] << ' ';
            }
            // cout << '\n';
        }


        vector<ll> cur(v[t].size(), LLONG_MAX);
        if (t == 1) {
            for (int j = 0; j < v[t].size(); ++j) {
                cur[j] = min(cur[j], cache[0][j] + prv[0]);
            }
        } else {
            for (int j = 0; j < v[t].size(); ++j) {
                for (int i = 0; i < v[t - 1].size(); ++i)
                    cur[j] = min(cur[j], cache[i][j] + prv[i]);
            }
        }
        prv = cur;
    }

    cout << prv[(int) v.back().size() - 1] << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << '\n';
        solve();
        cout.flush();
    }
}