#include <bits/stdc++.h>
using namespace std;

int N, K;
int a[200000];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> K;
    for (int i = 0; i < N; ++i) cin >> a[i];
    int ans = 0;
    int mn = a[0], mx = a[0];
    for (int i = 0; i < N; ++i) {
        mn = min(mn, a[i]);
        mx = max(mx, a[i]);
        if (mx - mn + 1 > K) {
            ++ans;
            mn = a[i], mx = a[i];
        }
    }
    cout << ans;
}