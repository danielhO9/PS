#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<double>> SquareMatrix;
 
SquareMatrix operator * (const SquareMatrix &a, const SquareMatrix &b) {
    int size = a.size();
    SquareMatrix res(size, vector<double>(size));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return res;
}

SquareMatrix identity(int n) {
	SquareMatrix res(n, vector<double>(n));
	for (int i = 0; i < n; ++i) res[i][i] = 1.0;
	return res;
}
 
SquareMatrix pow(const SquareMatrix& A, int m) {
	if (m == 0) return identity(A.size());
	if (m % 2 > 0) return pow(A, m - 1) * A;
	SquareMatrix half = pow(A, m / 2);
	return half * half;
}