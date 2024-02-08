#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL MOD = 1000000007;
int T, N, D;
vector<vector<LL>> table[101];

vector<vector<LL>> multiplication(vector<vector<LL>>& A, vector<vector<LL>>& B) {
	vector<vector<LL>> ret(N, vector<LL> (N, 0));
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
		for (int k = 0; k < N; ++k) {
			ret[i][j] += A[i][k] * B[k][j];
			ret[i][j] %= MOD;
		}
	}
	return ret;
}

vector<vector<LL>> power(vector<vector<LL>>& A, int b) {
	if (b == 0) {
		vector<vector<LL>> ret(N, vector<LL>(N, 0));
		for (int i = 0; i < N; ++i) ret[i][i] = 1;
		return ret;
	}
	if (b == 1) return A;
	vector<vector<LL>> half = power(A, b / 2);
	vector<vector<LL>> ret1 = multiplication(half, half);
	if (b % 2 == 0) return ret1;
	vector<vector<LL>> ret2 = multiplication(ret1, A);
	return ret2;
}

vector<vector<LL>> solve() {
	vector<vector<LL>> ret1;
	vector<vector<LL>> ret2;
	ret1 = power(table[T], D / T);
	ret2 = multiplication(ret1, table[D % T]);
	return ret2;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> T >> N >> D;
	vector<vector<LL>> temp(N, vector<LL> (N, 0));
	for (int i = 0; i < N; ++i) temp[i][i] = 1;
	table[0] = temp;
	int M, a, b; LL c;
	for (int i = 1; i <= T; ++i) {
		for (int j = 0; j < N; ++j) for (int k = 0; k < N; ++k) temp[j][k] = 0;
		cin >> M;
		for (int j = 0; j < M; ++j) {
			cin >> a >> b >> c;
			--a; --b;
			temp[a][b] = c;
		}
		if (i == 1) table[i] = temp;
		else table[i] = multiplication(table[i - 1], temp);
	}
	vector<vector<LL>> ans = solve();
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cout << ans[i][j] << ' ';
		}
		cout << '\n';
	}
}