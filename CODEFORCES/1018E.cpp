#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
string s;

void solve() {
    cin >> n >> s;
    vector<ll> v[2];
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'P') v[i % 2].push_back(1);
        else v[i % 2].push_back(0);
    }
    vector<ll> tar[2];
    for (int i = 0; i < 2; ++i) {
        tar[i] = v[i];
        sort(tar[i].begin(), tar[i].end());
    }
    ll ans = 0;
    for (int i = 0; i < 2; ++i) {
        vector<ll> psm(v[i].size());
        for (int j = 0; j < v[i].size(); ++j) {
            if (j == 0) psm[j] = v[i][j];
            else psm[j] = psm[j - 1] + v[i][j];
        }
        vector<ll> psm_tar(v[i].size());
        for (int j = 0; j < v[i].size(); ++j) {
            if (j == 0) psm_tar[j] = tar[i][j];
            else psm_tar[j] = psm_tar[j - 1] + tar[i][j];
        }
        for (int j = 0; j < v[i].size(); ++j) ans += abs(psm_tar[j] - psm[j]);
    }
    int bcnt[2] = {0, 0};
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < v[i].size(); ++j) if (v[i][j] == 0) ++bcnt[i];
    }
    int p[2];
    for (int i = 0; i < 2; ++i) {
        if (i == 0) p[i] = bcnt[i] * 2;
        else p[i] = bcnt[i] * 2 + 1;
    }
    int tmp = abs(p[0] - p[1]) / 2;
    for (int i = 1; i <= tmp; ++i) ans += (i + 1) / 2;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}