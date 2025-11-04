#include <bits/stdc++.h>
using namespace std;

const int SZ = 64;

struct MatrixVector {
    vector<uint64_t> m;

    MatrixVector(): MatrixVector(false) {}
    MatrixVector(bool init) {
        m.resize(SZ);
        if (init) for (int i = 0; i < SZ; ++i) m[i] = (1ull << i);
    }

    MatrixVector t() const {
        MatrixVector ret {};
        for (int i = 0; i < SZ; ++i) {
            ret.m[i] = 0ull;
            for (int j = 0; j < SZ; ++j) if ((*this)(j, i)) ret.m[i] ^= (1ull << j);
        }
        return ret;
    }
    MatrixVector operator*(const MatrixVector& _A) const {
        auto A = _A.t();
        MatrixVector ret {};
        for (int i = 0; i < SZ; ++i) for (int j = 0; j < SZ; ++j) {
            if (__builtin_popcountll(m[i] & A.m[j]) & 1) ret.set(i, j, true);
        }
        return ret;
    }
    uint64_t operator*(const uint64_t& x) {
        uint64_t ret = 0;
        for (int i = 0; i < SZ; ++i) {
            if (__builtin_popcountll(m[i] & x) & 1) ret ^= (1ull << i);
        }
        return ret;
    }

    const bool operator() (int r, int c) const { return (m[r] >> c) & 1ull; }
    void set(int r, int c, bool x) {
        if ((*this)(r, c) == x) return;
        m[r] ^= (1ull << c);
    }
    void rswap(int i, int j) { swap(m[i], m[j]); }
    void rxor(int i, int j) { m[i] ^= m[j]; }
};

MatrixVector inverse(const MatrixVector& _A) {
    MatrixVector A = _A;
    MatrixVector ret {true};
    for (int j = 0, r = 0; j < SZ && r < SZ; ++j) {
        for (int i = r; i < SZ; ++i) {
            if (A(i, j)) {
                A.rswap(r, i);
                ret.rswap(r, i);
                break;
            }
        }
        if (A(r, j)) {
            for (int i = 0; i < SZ; ++i) if (i != r && A(i, r)) {
                A.rxor(i, r);
                ret.rxor(i, r);
            }
            ++r;
        }
    }
    return ret;
}

MatrixVector pow(const MatrixVector& _A, uint64_t n) {
    auto A = _A;
    MatrixVector res(true);
    while (n > 0) {
        if (n & 1ull) res = res * A;
        A = A * A;
        n >>= 1;
    }
    return res;
}


uint64_t xorshift64(uint64_t x) {
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return x;
}

const uint64_t N = ULLONG_MAX;
uint64_t primes[7] = {3, 5, 17, 257, 641, 65537, 6700417};
uint64_t rem[7];

MatrixVector A, B;

void init(uint64_t x, uint64_t t) {
    A = MatrixVector {};
    for (int i = 0; i < SZ; ++i) {
        uint64_t nxt = xorshift64(1ull << i);
        for (int j = 0; j < SZ; ++j) A.set(j, i, (nxt >> j) & 1ull);
    }
    MatrixVector X{}, Y{};
    for (int i = 0; i < SZ; ++i) {
        for (int j = 0; j < SZ; ++j) X.set(j, i, (x >> j) & 1ull);
        for (int j = 0; j < SZ; ++j) Y.set(j, i, (t >> j) & 1ull);
        x = xorshift64(x);
        t = xorshift64(t);
    }
    MatrixVector Xinv = inverse(X);
    B = Y * Xinv;
}

map<uint64_t, uint64_t> m;

uint64_t getRem(int pi) {
    uint64_t p = primes[pi];
    MatrixVector BB = pow(B, N / p);
    MatrixVector AA = pow(A, N / p);
    MatrixVector Ainv = inverse(AA);
    uint64_t len = p;
    uint64_t step = ceil(sqrt((long double)len));

    m.clear();
    MatrixVector Asqrt = pow(AA, step);
    uint64_t cur = 1, num = 0;
    while (num < len) {
        m[cur] = num;
        num += step;
        cur = Asqrt * cur;
    }
    cur = BB * 1ull;
    for (uint64_t i = 0; i < step; ++i) {
        if (m.find(cur) != m.end()) {
            return i + m[cur];
        }
        cur = Ainv * cur;
    }
    assert(false);
}

uint64_t pow(uint64_t a, uint64_t b, uint64_t mod) {
    if (b == 0) return 1ull;
    uint64_t h = pow(a, b >> 1ull, mod);
    h = (h * h) % mod;
    if (b & 1ull) return (a * h) % mod;
    return h;
}

void crt(uint64_t& r1, uint64_t& p1, uint64_t r2, uint64_t p2) {
    uint64_t x = p2 + r2 - (r1 % p2);
    x %= p2;
    x *= pow(p1 % p2, p2 - 2, p2);
    x %= p2;
    r1 = r1 + x * p1;
    p1 *= p2;
}

int main() {
    uint64_t x, t; cin >> x >> t;
    init(x, t);
    for (int i = 0; i < 7; ++i) rem[i] = getRem(i);
    uint64_t r1 = rem[0], p1 = primes[0];
    for (int i = 1; i < 7; ++i) crt(r1, p1, rem[i], primes[i]);
    cout << r1 + 1;
}