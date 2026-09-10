#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
{1} * (K - 1): lose
piles <= K && stones >= K: win
stones < K: lose
(preserve # of piles) or (stones < K): win

piles == K + 1일 때
    min(stones) < K: win
    all K: lose
*/

ll K;
ll A[200001];

void solve() {
    cin >> K;
    for (int i = 0; i < K + 1; ++i) cin >> A[i];
    ll mn = LLONG_MAX;
    for (int i = 0; i < K + 1; ++i) mn = min(mn, A[i] / K);
    for (int i = 0; i < K + 1; ++i) A[i] -= mn * K;
    ll sm = 0, cnt = 0;
    for (int i = 0; i < K + 1; ++i) sm += A[i];
    for (int i = 0; i < K + 1; ++i) if (A[i]) ++cnt;
    if (cnt == K + 1) cout << "Alice\n";
    else if (sm >= K) cout << "Alice\n";
    else cout << "Bob\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}