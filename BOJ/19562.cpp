#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 998244353;

ll pow(ll a, ll x) {
	if (x == 0) return 1ll;
	ll half = pow(a, x / 2);
	half = (half * half) % MOD;
	if (x % 2) return (half * a) % MOD;
	else return half;
}

ll inv(ll x) { return pow(x, MOD - 2); }

template<class T>
class Matrix {
public:
    int m, n;
	vector<int> cidx;
    vector<vector<T>> entry;
    Matrix(int m_, int n_) : m(m_), n(n_), cidx(n_), entry(m_, vector<T>(n_)) {
		iota(cidx.begin(), cidx.end(), 0);
	}
    Matrix(int m_) : Matrix(m_, m_) {}

    T& operator[](const pair<int, int>& p) { return entry[p.first][cidx[p.second]]; }

    const T& operator[](const pair<int, int>& p) const { return entry[p.first][cidx[p.second]]; }

    void rswap(int i, int j) { swap(entry[i], entry[j]); }

    void rmul(int i, T x) {
        for (int j = 0; j < n; ++j) {
            entry[i][j] *= x;
			entry[i][j] %= MOD;
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
vector<T> char_poly(Matrix<T>& A) {
	int n = A.n;
	assert(n == A.n);
	for (int j = 0; j < n - 2; ++j) {
		for (int i = j + 1; i < n; ++i) {
			if (A[{i, j}] != 0) {
				A.rswap(i, j + 1);
				A.cswap(i, j + 1);
				break;
			}
		}
		if (A[{j + 1, j}] != 0) {
			for (int i = j + 2; i < n; ++i) {
				T x = (-A[{i, j}] + MOD) % MOD;
				x *= inv(A[{j + 1, j}]); x %= MOD;
				A.radd(i, j + 1, x);
				A.cadd(j + 1, i, (-x + MOD) % MOD);
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) cout << A[{i, j}] << ' ';
		cout << '\n';
	}
	vector<vector<T>> cache(n + 1);
	cache[0] = {1};
	for (int k = 1; k <= n; ++k) {
		cache[k].resize(k + 1);
		for (int i = 1; i <= k; ++i) {
			cache[k][i] = cache[k - 1][i - 1];
		}
		for (int i = 0; i < k; ++i) {
			cache[k][i] -= (A[{k - 1, k - 1}] * cache[k - 1][i]) % MOD;
			cache[k][i] += MOD; cache[k][i] %= MOD;
		}
		T prod = 1;
		for (int i = k - 2; i >= 0; --i) {
			prod *= A[{i + 1, i}];
			prod %= MOD;
			for (int j = 0; j <= i; ++j) {
				cache[k][j] -= (((A[{i, k - 1}] * prod) % MOD) * cache[i][j]) % MOD;
				cache[k][j] += MOD; cache[k][j] %= MOD;
			}
		}
	}
	return cache[n];
}

void solve() {
	int n; cin >> n; int Q; cin >> Q;
	Matrix<ll> A(n);
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> A[{i, j}];
	auto poly = char_poly(A);
	if (n % 2) {
		for (auto& i: poly) {
			i *= -1;
			i += MOD;
			i %= MOD;
		}
	}
	// for (auto i: poly) cout << i << ' ';
	// cout << '\n';
	for (int i = 0; i < Q; ++i) {
		ll x; cin >> x;
		ll now = 1ll;
		ll ans = 0ll;
		for (int i = 0; i <= n; ++i) {
			ans += (poly[i] * now) % MOD;
			ans %= MOD;
			now *= x;
			now %= MOD;
		}
		cout << ans << ' ';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}