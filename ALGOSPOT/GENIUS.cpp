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

int n, k, m, length[50];
double T[50][50];

vector<double> getProb() {
	SquareMatrix W(4 * n, vector<double>(4 * n));
	for (int i = 0; i < 3 * n; ++i) W[i][i + n] = 1.0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			W[3 * n + i][(4 - length[j]) * n + j] = T[j][i];
		}
	}
	SquareMatrix Wk = pow(W, k);
	vector<double> ret(n);
	for (int song = 0; song < n; ++song) {
		for (int start = 0; start < length[song]; ++start) {
			ret[song] += Wk[(3 - start) * n + song][3 * n];
		}
	}
	return ret;
}

void solve() {
	cin >> n >> k >> m;
	for (int i = 0; i < n; ++i) cin >> length[i];
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> T[i][j];
	vector<double> ans = getProb();
	vector<int> fav(m);
	for (int i = 0; i < m; ++i) cin >> fav[i];
	cout << fixed;
	cout.precision(8);
	for (auto i: fav) cout << ans[i] << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}

/*
3 0 3
4 4 2
0.18 0.40 0.42
0.15 0.46 0.39
0.58 0.23 0.19
0 1 2
*/