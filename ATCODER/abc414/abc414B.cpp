#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;

void solve() {
    cin >> N;
    vector<pair<char, ll>> v(N);
    ll sm = 0;
    bool flag = true;
    for (int i = 0; i < N; ++i) {
        cin >> v[i].first >> v[i].second;
        if (v[i].second > 100) flag = false;
        if (flag) {
            sm += v[i].second;
            if (sm > 100) flag = false;
        }
    }
    if (flag) {
        for (auto [i, j]: v) {
            for (int k = 0; k < j; ++k) cout << i;
        }
    } else cout << "Too Long";

}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}