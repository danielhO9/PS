#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<vector<ll>> SquareMatrix;
ll MOD = 1000000007;
const SquareMatrix base = {{1, 1, 1}, {1, 2, 1}, {1, 1, 2}};
 
SquareMatrix operator * (const SquareMatrix &a, const SquareMatrix &b) {
    int size = a.size();
    SquareMatrix res(size, vector<ll>(size));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                res[i][j] += a[i][k] * b[k][j];
				res[i][j] %= MOD;
            }
        }
    }
    return res;
}

SquareMatrix identity(int n) {
	SquareMatrix res(n, vector<ll>(n));
	for (int i = 0; i < n; ++i) res[i][i] = 1ll;
	return res;
}
 
SquareMatrix pow(const SquareMatrix& A, ll m) {
	if (m == 0) return identity(A.size());
	if (m % 2 > 0) return pow(A, m - 1) * A;
	SquareMatrix half = pow(A, m / 2);
	return half * half;
}

void solve() {
	ll N; cin >> N;
	if (N % 2 == 1) {
		cout << 0; return;
	}
	SquareMatrix ans = pow(base, N / 2);
	cout << (ans[0][0] + ans[0][1] + ans[0][2]) % MOD;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}