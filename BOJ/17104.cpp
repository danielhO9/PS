#include <bits/stdc++.h>
using namespace std;
typedef complex<double> base;

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

vector<int> nonPrime(1000000);
vector<bool> prime(500000);
vector<int> todo(1000001);
// 1 빼고 2로 나눈 값으로

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    nonPrime[0] = nonPrime[1] = 1; int temp;
    for (int i = 2; i < 1000000; ++i) {
        if (!nonPrime[i]) {
            prime[(i - 1) / 2] = 1;
            if (2 * i < 1000000) ++todo[2 * i];
            temp = 2 * i;
            while (temp < 1000000) {
                nonPrime[temp] = 1;
                temp += i;
            }
        }
    }
    prime[0] = 0;
    vector<base> cal1(prime.begin(), prime.end());
    vector<base> cal2(prime.begin(), prime.end());
    multiply(cal1, cal2);
    int T, x; cin >> T;
    for (int i = 0; i < T; ++i) {
        cin >> x;
        if (x == 4) cout << 1 << "\n";
        else {
            temp = (int) round(cal1[(x - 2) / 2].real());
            cout << (temp - todo[x]) / 2 + todo[x] << "\n";
        }
    }
    return 0;
}