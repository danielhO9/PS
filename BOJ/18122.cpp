#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

ll a[1000001], b[1000001];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    a[1] = 2, b[1] = 3;
    int N; cin >> N;
    for (int i = 1; i <= N; ++i) {
        a[i] = a[i - 1] + 2 + a[i - 1];
        a[i] %= MOD;
        b[i] = a[i - 1] + 1 + a[i - 1] + 1 + a[i - 1] + 1 + a[i - 1];
        b[i] %= MOD;
    }
    cout << b[N];
}