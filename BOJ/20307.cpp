#include <bits/stdc++.h>
using namespace std;
typedef __int128 ll;

ll gcd(ll a, ll b) {
	if (a < b) swap(a, b);
	if (b == 0) return a;
	return gcd(b, a % b);
}

struct fraction {
	ll a, b;
};

ll absd(ll x) {
	if (x < 0) return -x;
	else return x;
}

fraction operator+(fraction f1, fraction f2) {
	f1.a *= f2.b;
	f2.a *= f1.b;
	fraction ret = {f1.a + f2.a, f1.b * f2.b};
	if (ret.a == 0) return {0, 1};
	ll g = gcd(absd(ret.a), absd(ret.b));
	ret.a /= g; ret.b /= g;
	return ret;
}

fraction operator*(fraction f, int t) {
	fraction ret = f;
	ret.a *= t;
	ll g = gcd(absd(ret.a), absd(ret.b));
	ret.a /= g; ret.b /= g;
	return ret;
}

fraction operator*(fraction f1, fraction f2) {
	fraction ret;
	ret.a = f1.a * f2.a;
	ret.b = f1.b * f2.b;
	if (ret.a == 0) return {0, 1};
	ll g = gcd(absd(ret.a), absd(ret.b));
	ret.a /= g; ret.b /= g;
	return ret;
}

bool operator!=(fraction f, int t) {
	return f.a != f.b * t;
}

fraction operator-(fraction f) {
	return {-f.a, f.b};
}

fraction inv(fraction f) {
	if (f.a == 0) return f;
	if (f.a < 0) return {-f.b, -f.a};
	return {f.b, f.a};
}

template<class T>
class matrix {
public:
    int n, m;
    vector<vector<T>> entry;

    matrix(int n_, int m_) : n(n_), m(m_), entry(n_, vector<T>(m_)) {}
    matrix(int n_) : matrix(n_, n_) {}

    T& operator[](const pair<int, int>& p) {
        return entry[p.first][p.second];
    }

    const T& operator[](const pair<int, int>& p) const {
        return entry[p.first][p.second];
    }

    void rswap(int i, int j) {
        swap(entry[i], entry[j]);
    }

    void rmul(int i, T x) {
        for (int j = 0; j < m; j++) {
            entry[i][j] = entry[i][j] * x;
        }
    }

    void radd(int i1, int i2, T x) {
        for (int j = 0; j < m; j++) {
			auto tmp = entry[i2][j] * x;
			auto ttmp = tmp + entry[i1][j];
            entry[i1][j] = ttmp;
        }
    }
};

template<class T>
void rref(matrix<T>& A) {
    for (int j = 0, r = 0; j < A.m && r < A.n; j++) {
		// for (int i = 0; i < A.n; ++i) {
		// 	for (int j = 0; j < A.m; ++j) {
		// 		cout << A[{i, j}].a << '/' << A[{i, j}].b << ' ';
		// 	}
		// 	cout << '\n';
		// }
		// cout << '\n';
        for (int i = r; i < A.n; i++) {
            if (A[{i, j}] != 0) {
                A.rswap(r, i);
                break;
            }
        }
		// cout << "swap\n";
		// for (int i = 0; i < A.n; ++i) {
		// 	for (int j = 0; j < A.m; ++j) {
		// 		cout << A[{i, j}].a << '/' << A[{i, j}].b << ' ';
		// 	}
		// 	cout << '\n';
		// }
		// cout << '\n';
		// cout << "ero\n";
        if (A[{r, j}] != 0) {
            A.rmul(r, inv(A[{r, j}]));
            for (int i = 0; i < A.n; i++) {
                if (i != r) {
					// cout << (-A[{i, j}]).a << '/' << (-A[{i, j}]).b << '\n';
                    A.radd(i, r, -A[{i, j}]);
                }
            }
            r++;
        }
		// for (int i = 0; i < A.n; ++i) {
		// 	for (int j = 0; j < A.m; ++j) {
		// 		cout << A[{i, j}].a << '/' << A[{i, j}].b << ' ';
		// 	}
		// 	cout << '\n';
		// }
		// cout << '\n';
    }
}

void solve() {
	int n, m; cin >> n >> m;
	matrix<fraction> mat(n, m);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			string tmp; cin >> tmp;
			int a, b;
			if (tmp.size() == 1) {
				a = stoi(tmp);
				b = 1;
			} else if (tmp.size() == 3) {
				a = tmp[0] - '0';
				b = tmp[2] - '0';
			} else if (tmp.size() == 2) {
				a = tmp[1] - '0';
				a *= -1;
				b = 1;
			} else {
				a = tmp[1] - '0';
				b = tmp[3] - '0';
				a *= -1;
			}
			mat[{i, j}] = {a, b};
		}
	}
	rref(mat);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (mat[{i, j}].b == 1) {
				long long a = mat[{i, j}].a;
				cout << a << ' ';
			}
			else {
				long long a = mat[{i, j}].a;
				long long b = mat[{i, j}].b;
				cout << a << '/' << b << ' ';
			}
		}
		cout << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}