#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N;
bool dig[10];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    int n = N;
    while (n) {
        dig[n % 10] = true;
        n /= 10;
    }
    ll ans = 0, p = 1;
    while (true) {
        ll cur = N * p + ans;
        bool flag = true;
        for (int i = 2; i < 10; ++i) if (dig[i] && cur % i) flag = false;
        if (flag) { cout << cur; return 0; }
        ++ans; if (ans == p) { ans = 0; p *= 10; } 
    }
}