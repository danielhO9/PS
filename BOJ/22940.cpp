#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename T>
struct Matrix {
    int m, n;
	vector<int> cidx;
    vector<vector<T>> entry;
    Matrix(int m, int n) : m(m), n(n), cidx(n), entry(m, vector<T>(n)) { iota(cidx.begin(), cidx.end(), 0); }
    Matrix(int m_) : Matrix(m_, m_) {}

    T& operator() (int r, int c) { assert(0 <= r && r < m && 0 <= c && c < n); return entry[r][cidx[c]]; }
    const T& operator() (int r, int c) const { assert(0 <= r && r < m && 0 <= c && c < n); return entry[r][cidx[c]]; }
    Matrix operator*(const Matrix& A) const {
        assert(n == A.m);
        Matrix ret{m, A.n};
        for (int i = 0; i < ret.m; ++i) for (int k = 0; k < A.n; ++k) for (int j = 0; j < ret.n; ++j) 
            ret[{i, j}] += entry[i][k] * A(k, j);
        return ret;
    }
    void rswap(int i, int j) { swap(entry[i], entry[j]); }
    void rmul(int i, T x) { for (int j = 0; j < n; ++j) entry[i][j] *= x; }
    void rdiv(int i, T x) { for (int j = 0; j < n; ++j) entry[i][j] /= x; }
    void radd(int i1, int i2, T x) { for (int j = 0; j < n; ++j) entry[i1][j] += entry[i2][j] * x; }
	void cswap(int i, int j) { swap(cidx[i], cidx[j]); };
	void cmul(int j, T x) { for (int i = 0; i < n; ++i) entry[i][cidx[j]] *= x; }
	void cadd(int j1, int j2, T x) { for (int i = 0; i < n; ++i) entry[i][cidx[j1]] += entry[i][cidx[j2]] * x; }
};

template<typename T>
void rref(Matrix<T>& A) {
    for (int j = 0, r = 0; j < A.n && r < A.m; ++j) {
        for (int i = r; i < A.m; ++i) {
            if (A(i, j) != 0) {
                A.rswap(r, i);
                break;
            }
        }
        if (A(r, j) != 0) {
            A.rmul(r, 1 / A(r, j));
            for (int i = r; i < A.m; ++i) if (i != r)  A.radd(i, r, -A(i, r));
            ++r;
        }
    }
}

int N;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    Matrix<double> A {N, N + 1};
    vector<double> x(N);
    for (int i = 0; i < N; ++i) for (int j = 0; j < N + 1; ++j) cin >> A(i, j);
    rref(A);
    // for (int i = 0; i < N; ++i) {
    //     for (int j = 0; j < N + 1; ++j) cout << A(i, j) << ' ';
    //     cout << '\n';
    // }
    for (int i = N - 1; i >= 0; --i) {
        double y = A(i, N);
        for (int j = i + 1; j < N; ++j) y -= x[j] * A(i, j);
        y /= A(i, i);
        x[i] = y;
    }
    for (int i = 0; i < N; ++i) cout << (int)(x[i]+0.5) << ' ';
}