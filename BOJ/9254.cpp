#include <bits/stdc++.h>
using namespace std;

template<class T>
class Matrix {
public:
    int m, n;
    vector<vector<T>> entry;
    Matrix(int m_, int n_) : m(m_), n(n_), entry(m_, vector<T>(n_)) {}
    Matrix(int m_) : Matrix(m_, m_) {}

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
        for (int j = 0; j < n; ++j) {
            entry[i][j] *= x;
        }
    }

    void radd(int i1, int i2, T x) {
        for (int j = 0; j < n; ++j) {
            entry[i1][j] += entry[i2][j] * x;
        }
    }
};

template<class T>
void rref(Matrix<T>& A) {
    for (int j = 0, r = 0; j < A.n && r < A.m; ++j) {
        for (int i = r; i < A.m; i++) {
            if (A[{i, j}] != 0) {
                A.rswap(r, i);
                break;
            }
        }
        if (A[{r, j}] != 0) {
            A.rmul(r, 1 / A[{r, j}]);
            for (int i = 0; i < A.m; ++i) {
                if (i != r) {
                    A.radd(i, r, -A[{i, j}]);
                }
            }
            ++r;
        }
    }
}

template<class T>
Matrix<T> inv(const Matrix<T>& A) {
    int n = A.n;
    Matrix<T> B(n, n + n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            B[{i, j}] = A[{i, j}];
            B[{i, n + i}] = 1;
        }
    }
    rref(B);
    Matrix<T> X(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            X[{i, j}] = B[{i, n + j}];
        }
    }
    return X;
}

template<class T>
T det(Matrix<T>& A) {
    T ret = 1;
    for (int j = 0; j < A.n; ++j) {
        for (int i = j; i < A.n; ++i) {
            if (A[{i, j}] != 0) {
                if (i > j) {
                    A.rswap(j, i);
                    ret = -ret;
                }
                break;
            }
        }
        if (A[{j, j}] == 0) {
            return 0;
        }
        ret *= A[{j, j}];
        A.rmul(j, 1 / A[{j, j}]);
        for (int i = j + 1; i < A.n; ++i) {
            A.radd(i, j, -A[{i, j}]);
        }
    }
    return ret;
}

void solve() {
	int n; cin >> n;
	Matrix<double> A(n);
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> A[{i, j}];
	Matrix<double> B = A;
	if (det(B) == 0) {
		cout << "no inverse";
		return;
	}
	Matrix<double> X = inv(A);
	cout << fixed;
	cout.precision(7);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) cout << X[{i, j}] << ' ';
		cout << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}