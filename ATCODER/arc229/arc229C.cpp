#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N;
ll A[200000];

ll f() {
    ll ans = 0;
    for (int i = 0; i < N - 1; ++i) {
        ans += ((A[i] + A[i + 1]) >> 1);
    }
    return ans;
}

void solve() {
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> A[i];
    vector<ll> v[2];
    for (int i = 0; i < N; ++i) {
        v[A[i] & 1].push_back(A[i]);
    }
    for (int i = 0; i < 2; ++i) {
        sort(v[i].begin(), v[i].end());
        reverse(v[i].begin(), v[i].end());
    }
    
    ll ans = LLONG_MAX;

    for (int i = 0; i < 2; ++i) {
        int j = (i ^ 1);
        for (int k = 0; k < N; ++k) A[k] = -1;
        if (v[i].size() >= 2) {
            A[0] = v[i][0];
            A[N - 1] = v[i][1];
            int tmp = -1;
            for (int k = 2; k < v[i].size(); ++k) {
                if (2 * (k - 1) >= N - 1) {
                    tmp = k;
                    break;
                }
                A[2 * k - 2] = v[i][k];
            }
            if (tmp != -1) {
                // cout << tmp << '\n';
                for (int k = 0; k < N; ++k) if (A[k] == -1 && tmp < v[i].size()) A[k] = v[i][tmp++];
            }
            int idx = 0;
            for (int k = 0; k < N; ++k) if (A[k] == -1) A[k] = v[j][idx++];
            
            ans = min(ans, f());
        }
    }
    for (int k = 0; k < N; ++k) A[k] = -1;
    if (v[0].size() > v[1].size()) swap(v[0], v[1]);
    for (int k = 0; k < v[0].size(); ++k) {
        A[2 * k] = v[0][k];
    }
    int idx = 0;
    for (int k = N - 1; k >= 0; --k) if (A[k] == -1) A[k] = v[1][idx++];
    ans = min(ans, f());
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}