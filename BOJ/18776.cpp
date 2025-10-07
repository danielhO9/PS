#include <bits/stdc++.h>
using namespace std;

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
            if (entry[i][cidx[k]] & A(k, j)) ret(i, j) ^= 1;
        return ret;
    }
    uint32_t operator*(const uint32_t& x) {
        uint32_t ret = 0;
        for (int i = 0; i < 32; ++i) {
            int tmp = 0;
            for (int j = 0; j < 32; ++j) if (entry[i][cidx[j]] & (x >> j)) {
                tmp ^= 1;
            }
            if (tmp) ret |= (1 << i);
        }
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
            for (int i = 0; i < A.m; ++i) if (i != r && A(i, r)) {
                for (int k = 0; k < A.n; ++k) A(i, k) ^= A(r, k);
            }
            ++r;
        }
    }
}

template<typename T>
Matrix<T> inverse(const Matrix<T>& A) {
    assert(A.n == A.m);
    int n = A.n;
    Matrix<T> B {n, 2 * n};
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) B(i, j) = A(i, j);
    for (int i = 0; i < n; ++i) B(i, i + n) = 1;
    rref(B);
    Matrix<T> ret {n, n};
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) ret(i, j) = B(i, j + n);
    return ret;
}

template<typename T>
Matrix<T> pow(const Matrix<T>& A, long long n) {
    assert(A.n == A.m);
    if (n == 0) {
        Matrix<T> ret {A.n};
        for (int i = 0; i < A.n; ++i) ret(i, i) = 1;
        return ret;
    }
    auto H = pow(A, n / 2);
    H = H * H;
    if (n % 2) return H * A;
    else return H;
}

uint32_t xorshift32(uint32_t x) {
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return x;
}

unordered_map<uint32_t, uint32_t> m;

int main() {
    Matrix<int> A {32};
    for (int i = 0; i < 32; ++i) {
        uint32_t tmp = xorshift32(1 << i);
        for (int j = 0; j < 32; ++j) A(j, i) = ((tmp >> j) & 1);
    }
    Matrix<int> Ainv = inverse(A);
    uint32_t sqrt = (1 << 16);
    Matrix<int> Asqrt = pow(A, sqrt);
    uint32_t x, t; cin >> x >> t;
    for (uint32_t i = 0; i < sqrt; ++i) {
        assert(x != 0);
        if (m.find(x) == m.end()) m[x] = sqrt * i;
        x = Asqrt * x;
    }
    uint32_t ans = 4294967295ll;
    for (uint32_t i = 0; i < sqrt; ++i) {
        if (m.find(t) != m.end()) ans = min(ans, i + m[t]);
        t = Ainv * t;
    }
    cout << ans + 1;
}