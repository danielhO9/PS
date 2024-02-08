#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    ll N, M; cin >> N >> M; long long answer = 0;
    vector<ll> A(N + 1, 0); vector<ll> S(N + 1, 0); vector<ll> cnt(M, 0);
    for (ll i = 1; i <= N; ++i) {
        cin >> A[i];
        S[i] = S[i - 1] + A[i];
        cnt[S[i] % M] += 1;
    }
    for (ll i = 0; i < M; ++i) {
        if (i == 0) answer += cnt[i];
        answer += (cnt[i] * (cnt[i] - 1)) / 2;
    }
    cout << answer;
    return 0;
}