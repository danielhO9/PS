#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, K;
ll C[10000];

void solve() {
    cin >> N >> K;
    for (int i = 0; i < N; ++i) cin >> C[i];
    priority_queue<ll> pq;
    for (int i = 0; i < N; ++i) pq.push(-C[i]);
    ll ans = 0;
    ll rem = N % (K - 1);
    if (rem <= 1) rem += (K - 1);
    ll tmp = 0;
    for (int i = 0; i < rem; ++i) {
        if (pq.empty()) break;
        tmp += -pq.top();
        pq.pop();
    }
    pq.push(-tmp);
    ans += tmp;
    while (pq.size() >= 2) {
        tmp = 0;
        for (int i = 0; i < K; ++i) {
            if (pq.empty()) break;
            tmp += -pq.top();
            pq.pop();
        }
        pq.push(-tmp);
        ans += tmp;
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}