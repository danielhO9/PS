#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
string S;
ll arr[1000000];
ll tar[1000000];

void solve() {
    cin >> N >> S;
    N *= 2;
    for (int i = 0; i < N; ++i) arr[i] = (S[i] == 'A');
    for (int i = 1; i < N; ++i) arr[i] += arr[i - 1];
    for (int i = 0; i < N; ++i) tar[i] = (i % 2);
    for (int i = 1; i < N; ++i) tar[i] += tar[i - 1];
    ll ans = 0;
    for (int i = 0; i < N; ++i) ans += abs(tar[i] - arr[i]);
    ll tans = 0;
    for (int i = 0; i < N; ++i) tar[i] = ((i % 2)^ 1);
    for (int i = 1; i < N; ++i) tar[i] += tar[i - 1];
    for (int i = 0; i < N; ++i) tans += abs(tar[i] - arr[i]);
    cout << min(ans, tans);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}