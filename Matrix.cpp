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
void gaussian_elimination(Matrix<T>& A) {
    for (int j = 0, r = 0; j < A.n && r < A.m; ++j) {
        for (int i = r; i < A.m; ++i) {
            if (A[{i, j}] != 0) {
                A.rswap(r, i);
                break;
            }
        }
        if (A[{r, j}] != 0) {
            A.rmul(r, 1 / A[{r, j}]);
            for (int i = r + 1; i < A.m; ++i) {
                A.radd(i, r, -A[{i, j}]);
            }
            ++r;
        }
    }
}

template<size_t n>
void rref(vector<bitset<n>>& A) {
    int m = (int)A.size();
    for (int j = n - 1, r = 0; j >= 0 && r < m; --j) {
        for (int i = r; i < m; i++) {
            if (A[i][j]) {
                swap(A[r], A[i]);
                break;
            }
        }
        if (A[r][j]) {
            for (int i = 0; i < m; i++) if (i != r) {
                if (A[i][j]) {
                    A[i] ^= A[r];
                }
            }
            ++r;
        }
    }
}

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
T det(Matrix<T>& A) {
    assert(A.n == A.m);
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


template<class T>
Matrix<T> operator * (const Matrix<T>& A, const Matrix<T>& B) {
    assert(A.n == B.m);
    matrix<T> C(A.m, B.n);
    for (int i = 0; i < C.m; ++i) {
        for (int k = 0; k < A.n; ++k) {
            for (int j = 0; j < C.n; ++j) {
                C[{i, j}] += A[{i, k}] * B[{k, j}];
            }
        }
    }
    return C;
}

template<class T>
vector<T> solve_linear_equation(const Matrix<T>& A, const vector<T>& b) {
    int m = A.m;
    assert(m == A.n);
    assert(m == (int)b.size());
    matrix<T> B(m);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            B[{i, j}] = A[{i, j}];
        }
        B[{i, m}] = b[i];
    }
    rref(B);
    vector<T> x(m);
    for (int i = 0; i < m; ++i) {
        assert((B[{i, i}] == 1));
        x[i] = B[{i, m}];
    }
    return x;
}

template<class T>
Matrix<T> inv(const Matrix<T>& A) {
    int n = A.n;
    assert(n == A.m);
    matrix<T> B(n, n + n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            B[{i, j}] = A[{i, j}];
            B[{i, n + i}] = 1;
        }
    }
    rref(B);
    matrix<T> X(n);
    for (int i = 0; i < n; i++) {
        assert((B[{i, i}] == 1));
        for (int j = 0; j < n; j++) {
            X[{i, j}] = B[{i, n + j}];
        }
    }
    return X;
}