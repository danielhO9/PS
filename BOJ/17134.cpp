#include <bits/stdc++.h>
using namespace std;
typedef complex<double> base;

vector<bool> prime(1000001), semiPrime(1000001);

void fft(vector<base> &a, bool inv) {
    int n = (int) a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        while (!((j ^= bit) & bit)) bit >>= 1;
        if (i < j) swap(a[i], a[j]);
    }
    for (int i = 1; i < n; i <<= 1) {
        double x = inv ? M_PI / i : -M_PI / i;
        base w = {cos(x), sin(x)};
        for (int j = 0; j < n; j += i << 1) {
            base th = {1, 0};
            for (int k = 0; k < i; k++) {
                base tmp = a[i + j + k] * th;
                a[i + j + k] = a[j + k] - tmp;
                a[j + k] += tmp;
                th *= w;
            }
        }
    }
    if (inv) {
        for (int i = 0; i < n; i++) {
            a[i] /= n;
        }
    }
}

void multiply(vector<base> &a, vector<base> &b) {
    int n = (int) max(a.size(), b.size());
    int i = 0;
    while ((1 << i) < (n << 1)) i++;
    n = 1 << i;
    a.resize(n);
    b.resize(n);
    fft(a, false);
    fft(b, false);
    for (int i = 0; i < n; i++) {
        a[i] *= b[i];
    }
    fft(a, true);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    fill(prime.begin(), prime.end(), 1); prime[0] = prime[1] = false;
    for (int i = 2; i < 1000001; ++i) {
        if (prime[i]) {
            if (i * 2 <= 1000000) semiPrime[i * 2] = true;
            int j = i * 2;
            while (j <= 1000000) { prime[j] = false; j += i; }
        }
    }
    prime[2] = false;
    vector<base> p(prime.begin(), prime.end()), sp(semiPrime.begin(), semiPrime.end());
    multiply(p, sp);
    int T; cin >> T; int x;
    for (int i = 0; i < T; ++i) {
        cin >> x;
        cout << round(p[x].real()) << "\n";
    }
    return 0;
}