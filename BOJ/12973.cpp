#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
ll A, B;
int a[1000000];
ll val[1000001];
ll sm[1000001];
bool isPrime[100000];

void factorize(int n, map<int, ll>& v, ll t) {
    if (n <= 1) return;
    if (v.find(n) != v.end()) v[n] = min(v[n], t);
    else v[n] = t;
    for (int i = 2; i * i <= n; ++i) if (n % i == 0) {
        
        if (i >= 100000 || isPrime[i]) {
            if (v.find(i) != v.end()) v[i] = min(v[i], t);
            else v[i] = t;
        }

        if (n / i >= 100000 || isPrime[n / i]) {
            if (v.find(n / i) != v.end()) v[n / i] = min(v[n / i], t);
            else v[n / i] = t;
        }

    }
}

ll calc(int l, int r, int g) {
    ll mn = r, mx = l;
    for (ll i = l; i < r; ++i) {
        if (a[i] % g == 0) sm[i] = 0;
        else if ((a[i] - 1) % g == 0) sm[i] = B;
        else if ((a[i] + 1) % g == 0) sm[i] = B;
        else {
            mn = min(mn, i);
            mx = max(mx, i);
            sm[i] = 0;
        }
    }
    for (int i = l + 1; i < r; ++i) sm[i] += sm[i - 1];
    for (int i = l; i <= r; ++i) {
        if (i == l) val[i] = - A * i;
        else val[i] = sm[i - 1] - A * i;
    }

    ll ans = LLONG_MIN;
    if (mn == r) {
        mn = LLONG_MAX;
        for (int i = l; i <= r; ++i) {
            mn = min(mn, val[i]);
            if (mn != LLONG_MAX) ans = max(ans, val[i] - mn);
        }
        return -ans + sm[r - 1];
        
    }
    ll mmx = LLONG_MIN, mmn = LLONG_MAX;
    for (int i = l; i <= mn; ++i) {
        mmn = min(mmn, val[i]);
    }
    for (int i = mx + 1; i <= r; ++i) {
        mmx = max(mmx, val[i]);
    }
    return mmn - mmx + sm[r - 1];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    for (int i = 2; i < 100000; ++i) isPrime[i] = true;
    for (int i = 2; i < 100000; ++i) if (isPrime[i]) {
        for (int j = i * 2; j < 100000; j += i) isPrime[j] = false;
    }


    cin >> N >> A >> B;
    for (int i = 0; i < N; ++i) cin >> a[i];
    ll ans = LLONG_MAX;
    
    map<int, ll> s;
    factorize(a[0], s, 0);
    factorize(a[0] + 1, s, B);
    factorize(a[0] - 1, s, B);
    for (auto [i, j]: s) ans = min(ans, calc(1, N, i) + j);

    s.clear();
    factorize(a[N - 1], s, 0);
    factorize(a[N - 1] + 1, s, B);
    factorize(a[N - 1] - 1, s, B);
    for (auto [i, j]: s) ans = min(ans, calc(0, N - 1, i) + j);
    cout << ans;
}