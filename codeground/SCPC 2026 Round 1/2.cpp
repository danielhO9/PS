#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

int N;
ll arr[200000];
ll mx, mn;

void solve() {
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> arr[i];
    mx = LLONG_MIN, mn = LLONG_MAX;
    mx = max(mx, arr[2] - arr[0]);
    mx = max(mx, arr[N - 1] - arr[N - 3]);
    for (int i = 0; i < N - 3; ++i) {
        ll val = arr[i + 3] - arr[i];
        mx = max(mx, val / 2);
    }
    for (int i = 0; i < N - 2; ++i) {
        ll val = arr[i + 2] - arr[i];
        mn = min(mn, val / 2);
    }
    cout << mx << ' ' << mn << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i <<  '\n';
        solve();
        cout.flush();
    }
}