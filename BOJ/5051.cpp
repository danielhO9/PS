#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
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

LL n; vector<LL> square(500001);

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (LL i = 1; i < n; ++i) ++square[(i * i) % n];
    vector<base> lhs1(square.begin(), square.end());
    vector<base> rhs1(square.begin(), square.end());
    multiply(lhs1, rhs1);
    LL ret = 0, tempValue = 0;
    for (int i = 0; i < 2 * n - 1; ++i) ret += round(lhs1[i].real()) * square[i % n];
    for (int i = 0; i < n; ++i) tempValue += square[i] * square[(2 * i) % n];
    ret = (ret - tempValue) / 2 + tempValue;
    cout << ret;
    return 0;
}