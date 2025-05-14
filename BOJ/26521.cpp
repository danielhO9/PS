#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

ll a[5000];
ll x[5000];
ll n;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) {
        x[i] = 1;
        for (int j = 0; j < n; ++j) if (i != j) x[i] = ((a[i] - a[j]) * x[i]) % MOD;
        x[i] = (x[i] + MOD) % MOD;
        cout << x[i] << ' ';
    }
}