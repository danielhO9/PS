#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
int S[200000];

void solve() {
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> S[i];
    if (S[0] * 2 >= S[N - 1]) {
        cout << 2 << '\n';
        return;
    }
    vector<int> v;
    for (int i = 1; i + 1 < N; ++i) v.push_back(S[i]);
    sort(v.begin(), v.end());
    int ans = 1;
    int cur = S[0];
    while (cur * 2 < S[N - 1]) {
        auto idx = lower_bound(v.begin(), v.end(), cur * 2 + 1) - v.begin();
        if (idx == 0) break;
        --idx;
        if (v[idx] == cur) break;
        cur = v[idx];
        ++ans;
    }
    if (cur * 2 < S[N - 1]) cout << -1 << '\n';
    else cout << ans + 1 << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}