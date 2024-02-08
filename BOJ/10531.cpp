#include <bits/stdc++.h>
using namespace std;
typedef complex<double> base;

int N, M;
vector<base> k1(200001), k2(200001), k3(200001);

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
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N; int tmp;
    for (int i = 0; i < N; ++i) {
        cin >> tmp;
        k1[tmp] = base(1);
        k2[tmp] = base(1);
        k3[tmp] = base(1);
    }
    multiply(k1, k2);
    cin >> M;
    int ans = 0;
    for (int i = 0; i < M; ++i) {
        cin >> tmp;
        if (round(k1[tmp].real()) || round(k3[tmp].real())) ++ans;
    }
    cout << ans;
    return 0;
}