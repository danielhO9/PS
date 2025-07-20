#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MAX = 602;

ll N, M;
ll nxt[MAX];
ll cache[MAX];

void solve() {
    cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        int A, B; cin >> A >> B;
        nxt[A] = max((int) nxt[A], B);
    }
    for (ll i = 1; i < MAX; ++i) {
        for (ll j = 1; j <= 300; ++j) if (i >= j) {
            cache[i] = max(cache[i], j + cache[i + nxt[j] - j]);
        }
    }
    if (N < MAX) {
        cout << cache[N];
        return;
    }
    ll ans = 0;
    for (ll i = 1; i <= 300; ++i) {
        ll dif = i - nxt[i];
        ll cnt = (N - MAX + 1 + dif - 1) / dif;
        assert(N - cnt * dif < MAX);
        ans = max(ans, cnt * i + cache[N - cnt * dif]);
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}