#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N;
ll A[200000];
int prv[200000], nxt[200000];

void solve() {
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> A[i];
    for (int i = 0; i < N; ++i) {
        prv[i] = i - 1;
        nxt[i] = i + 1;
    }
    priority_queue<pair<ll, int>> pq;
    for (int i = 0; i < N; ++i) pq.push(make_pair(-A[i], -i));
    ll ans = 0;
    while (pq.size() > 1) {
        auto [val, i] = pq.top(); pq.pop();
        val *= -1;
        i *= -1;
        if (A[i] != val) continue;
        if (prv[i] == -1 && nxt[i] == N) break;
        int tar = prv[i];
        if (tar == -1 || (nxt[i] < N && A[prv[i]] > A[nxt[i]])) tar = nxt[i];
        if (A[tar] == A[i]) {
            prv[tar] = min(prv[i], prv[tar]);
            if (prv[tar] >= 0) nxt[prv[tar]] = tar;
            nxt[tar] = max(nxt[i], nxt[tar]);
            if (nxt[tar] < N) prv[nxt[tar]] = tar;
            ++A[tar];
            pq.push(make_pair(-A[tar], -tar));
            continue;
        }
        ans += A[tar] - A[i];
        A[i] = A[tar];
        pq.push(make_pair(-A[i], -i));
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}