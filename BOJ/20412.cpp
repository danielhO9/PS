#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll m, seed, x1, x2;

ll pow(ll a, ll b) {
    if (b == 0) return 1;
    ll h = pow(a, b / 2);
    h = (h * h) % m;
    if (b % 2) return (h * a) % m;
    else return h;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> m >> seed >> x1 >> x2;
    ll a = (((x1 - x2 + m) % m) * pow((seed - x1 + m) % m, m - 2)) % m;
    ll c = (x1 - (a * seed) % m + m) % m;
    cout << a << ' ' << c;
}