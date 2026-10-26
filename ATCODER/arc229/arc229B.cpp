#include <bits/stdc++.h>
using namespace std;

int N;
int A[30];
int cnt[30];

void solve() {
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> A[i];
    memset(cnt, 0, sizeof(cnt));
    for (int i = N - 1; i >= 0; --i) {
        int val = A[i];
        cnt[i] = A[i];
        for (int j = i; j >= 0; --j) {
            if (A[j] < val) {
                cout << "-1\n";
                return;
            }
            A[j] -= val;
            val <<= 1;
        }
    }
    if (cnt[N - 1]) cnt[N - 1] = 1;
    int tmp = cnt[N - 1];
    for (int i = N - 2; i >= 0; --i) {
        cnt[i] = max(cnt[i] - tmp, 0);
        tmp += cnt[i];
    }
    int ans = 0;
    for (int i = 0; i < N; ++i) ans += cnt[i];
    cout << ans << '\n';
    
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}