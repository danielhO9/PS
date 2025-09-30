#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N;
ll A[500000];
ll tar[500000];

void solve() {
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> A[i];
    ll sm = 0;
    for (int i = 0; i < N; ++i) sm += A[i];
    sm /= N;
    for (int i = 0; i < N; ++i) A[i] -= sm;
    
    int idx = 0; ll val = A[0];
    ll cur = 0;
    for (int i = 0; i < N; ++i) {
        cur += A[i];
        if (val > cur) {
            idx = i; val = cur;
        }
    }
    ll tmp = 0;
    ll ans = 0;
    for (int i = 0; i < N; ++i) {
        idx = (idx + 1) % N;
        tmp += A[idx];
        ans += tmp;
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}