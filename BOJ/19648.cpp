#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

// https://tistory.joonhyung.xyz
template<class T>
class Matrix {
public:
    int m, n;
	vector<int> cidx;
    vector<vector<T>> entry;
    Matrix(int m_, int n_) : m(m_), n(n_), cidx(n_), entry(m_, vector<T>(n_)) { iota(cidx.begin(), cidx.end(), 0); }
    Matrix(int m_) : Matrix(m_, m_) {}
    T& operator[](const pair<int, int>& p) { return entry[p.first][cidx[p.second]]; }
    const T& operator[](const pair<int, int>& p) const { return entry[p.first][cidx[p.second]]; }
};

template<class T>
Matrix<T> operator * (const Matrix<T> A, const Matrix<T> B) {
    assert(A.n == B.m);
    Matrix<T> C(A.m, B.n);
    for (int i = 0; i < C.m; ++i) {
        for (int k = 0; k < A.n; ++k) {
            for (int j = 0; j < C.n; ++j) {
                C[{i, j}] += (A[{i, k}] * B[{k, j}]) % MOD;
                C[{i, j}] %= MOD;
            }
        }
    }
    return C;
}

template<class T>
Matrix<T> pow(Matrix<T> A, ll x) {
    if (x == 0) {
        int n = A.n;
        Matrix<ll> B(n);
        for (int i = 0; i < n; ++i) B[{i, i}] = 1;
        return B;
    }
    Matrix<T> half = pow(A, x / 2);
    half = (half * half);
    if (x % 2) return half * A;
    return half;
}

int n;
vector<int> adj[14];
ll dis[14][14];
vector<pair<int, int>> edge = {
    {0, 1},
    {1, 0},
    {1, 2},
    {2, 3},
    {4, 0},
    {4, 1},
    {4, 3},
    {3, 5},
    {3, 6},
    {5, 6},
    {5, 4},
    {7, 4},
    {5, 8},
    {8, 7},
    {6, 9},
    {9, 13},
    {5, 13},
    {13, 8},
    {5, 9},
    {9, 10},
    {10, 11},
    {13, 11},
    {11, 8},
    {11, 12},
    {12, 8}
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (auto i: edge) adj[i.first].push_back(i.second);
    for (int i = 0; i < 14; ++i) for (int j = 0; j < 14; ++j) if (i != j) dis[i][j] = INT32_MAX;
    for (int i = 0; i < 14; ++i) for (int j: adj[i]) dis[i][j] = 1;
    for (int m = 0; m < 14; ++m) for (int s = 0; s < 14; ++s) for (int e = 0; e < 14; ++e) {
        dis[s][e] = min(dis[s][e], dis[s][m] + dis[m][e]);
    }
    Matrix<ll> M(14 * 14);
    for (int s1 = 0; s1 < 14; ++s1) for (int s2 = 0; s2 < 14; ++s2) if (dis[s1][s2] >= 3 && dis[s2][s1] >= 3) {
        for (auto e1: adj[s1]) for (auto e2: adj[s2]) {
            if (dis[e1][e2] >= 3 && dis[e2][e1] >= 3) ++M[{s1 * 14 + s2, e1 * 14 + e2}];
            // if (s1 == 4 && s2 == 13) cout << e1 << ' ' << e2 << ' ' << dis[e1][e2] << ' ' << dis[e2][e1] << '\n';
        }
    }
    Matrix<ll> P = pow(M, n);
    ll ans = 0;
    for (int i = 0; i < 14 * 14; ++i) ans += P[{4 * 14 + 13, i}], ans %= MOD;
    // for (int i = 0; i < 14 * 14; ++i) ans += P[{13 * 14 + 4, i}], ans %= MOD;
    cout << ans;
}