#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef complex<double> base;

void fft(vector<base> &a, bool inv) {
    LL n = a.size();
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
        for (int i = 0; i < n; i++) a[i] /= n;
    }
}

vector<LL> multiply(vector<LL> &A, vector<LL> &B) {
    vector<base> a(A.begin(), A.end()), b(B.begin(), B.end());
    LL n = max(a.size(), b.size());
    LL i = 0;
    while ((1 << i) < (n << 1)) i++;
    n = 1 << i;
    a.resize(n);
    b.resize(n);
    fft(a, false);
    fft(b, false);
    for (LL i = 0; i < n; i++) {
        a[i] *= b[i];
    }
    fft(a, true);
    vector<LL> ret;
    for (auto i: a) ret.push_back((LL) round(i.real()));
	while (ret.back() == 0) ret.pop_back();
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int N; vector<LL> X, Y;
    cin >> N; LL e;
    for (int i = 0; i < N; ++i) { cin >> e; X.push_back(e); }
    for (int i = 0; i < N; ++i) { cin >> e; Y.push_back(e); }
    vector<LL> ans = multiply(X, Y);
    LL ret = 0;
    for (int i = N - 1; i < 2 * N - 1; ++i) ret = max(ret, ans[i]);
    // cout << ret;
}