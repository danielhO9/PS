#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, M;
ll X[500000];
vector<ll> v;

void solve() {
    cin >> N >> M;
    for (int i = 0; i < N; ++i) cin >> X[i];
    sort(X, X + N);
    for (int i = 1; i < N; ++i) v.push_back(X[i] - X[i - 1]);
    sort(v.begin(), v.end());
    ll sm = 0;
    for (auto i: v) sm += i;
    reverse(v.begin(), v.end());
    for (int i = 0; i < M - 1; ++i) sm -= v[i];
    cout << sm;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}