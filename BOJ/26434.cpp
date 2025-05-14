#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
ll A[400001];
ll sm[400001];
ll ssm[400001];

void solve() {
    cin >> N;
    for (int i = 1; i <= N; ++i) cin >> A[i];
    for (int i = 1; i <= N; ++i) {
        sm[i] = sm[i - 1] + A[i];
        ssm[i] = ssm[i - 1] + sm[i];
    }
    // value increase, index decrease
    vector<pair<ll, int>> v;
    ll ans = 0;
    for (int i = N; i >= 1; --i) {
        ll cur = sm[i - 1];
        while (!v.empty() && v.back().first >= sm[i]) v.pop_back();
        v.push_back(make_pair(sm[i], i));
        // j >= i, sm[j] < sm[i - 1] for first
        int j;
        if (v.empty() || v.front().first >= cur) j = N;
        else {
            auto itr = lower_bound(v.begin(), v.end(), make_pair(cur, -1));
            --itr;
            j = itr->second - 1;
        }
        ans += (ssm[j] - ssm[i - 1]) - sm[i - 1] * (j - i + 1);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << ": ";
        solve();
    }
}