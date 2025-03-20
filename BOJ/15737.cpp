#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll P = 998244353;
const ll MOD = P;
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dist(1, P - 1);

ll pow(ll a, ll b) {
    if (b == 0) return 1;
    ll half = pow(a, b / 2);
    half = (half * half) % MOD;
    if (b % 2) return (a * half) % MOD;
    return half;
}

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

    void rswap(int i, int j) { swap(entry[i], entry[j]); }
    void rmul(int i, T x) {
        for (int j = 0; j < n; ++j) {
            entry[i][j] *= x; entry[i][j] %= MOD;
        }
    }
    void radd(int i1, int i2, T x) {
        for (int j = 0; j < n; ++j) {
            entry[i1][j] += (entry[i2][j] * x) % MOD;
            entry[i1][j] %= MOD;
        }
    }
	void cswap(int i, int j) { swap(cidx[i], cidx[j]); };
	void cmul(int j, T x) {
		for (int i = 0; i < n; ++i) {
			entry[i][cidx[j]] *= x;
            entry[i][cidx[j]] %= MOD;
		}
	}
	void cadd(int j1, int j2, T x) {
		for (int i = 0; i < n; ++i) {
			entry[i][cidx[j1]] += (entry[i][cidx[j2]] * x) % MOD;
            entry[i][cidx[j1]] %= MOD;
		}
	}
};

template<class T>
int matRank(Matrix<T>& A) {
    int r = 0;
    for (int j = 0; j < A.m && r < A.n; j++) {
        for (int i = r; i < A.n; i++) {
            if (A[{i, j}] != 0) {
                A.rswap(r, i);
                break;
            }
        }
        if (A[{r, j}] != 0) {
            A.rmul(r, pow(A[{r, j}], MOD - 2));
            for (int i = r + 1; i < A.n; i++) {
                A.radd(i, r, -A[{i, j}]);
            }
            r++;
        }
    }
    return r;
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int N, M; cin >> N >> M;
    Matrix<ll> A(N);
    for (int i = 0; i < M; ++i) {
        int u, v; cin >> u >> v; --u; --v;
        if (u > v) swap(u, v);
        A[{u, v}] = dist(gen);
        A[{v, u}] = pow(A[{u, v}], MOD - 2);
    }
    cout << matRank(A) / 2;
}