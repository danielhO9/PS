#include <bits/stdc++.h>
using namespace std;
typedef complex<double> base;

vector<complex<double>> A, B;

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
    string a, b;
    cin >> a >> b;
    if (a == "0" || b == "0") cout << 0;
    while (a != "") {
        A.push_back(base(((int) *a.rbegin()) - 48));
        a.pop_back();
    }
    while (b != "") {
        B.push_back(base(((int) *b.rbegin()) - 48));
        b.pop_back();
    }
    multiply(A, B);
    vector<int> answer;
    for (auto i: A) answer.push_back(round(i.real()));
    int tmp = 0;
    for (int i = 0; i < answer.size(); ++i) {
        answer[i] += tmp;
        if (answer[i] > 9) {
            tmp = answer[i] / 10;
            answer[i] %= 10;
        } else tmp = 0;
    }
    for(int i = answer.size() - 1; i >= 0; --i) {
        if (answer[i] == 0) answer.pop_back();
        else break;
    }
    for(int i = answer.size() - 1; i >= 0; --i) cout << answer[i];
    return 0;
}