#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL N, S, E, T, MOD = 1000003;
vector<vector<LL>> graph(50, vector<LL>(50, 0));

vector<vector<LL>> multiple(vector<vector<LL>>& A, vector<vector<LL>>& B) {
	vector<vector<LL>> ret(50, vector<LL>(50, 0));
	for (int i = 0; i < 50; ++i) for (int j = 0; j < 50; ++j) {
		ret[i][j] = 0;
		for (int k = 0; k < 50; ++k) {
			ret[i][j] += A[i][k] * B[k][j];
			ret[i][j] %= MOD;
		}
	}
	return ret;
}

vector<vector<LL>> pow(vector<vector<LL>>& g, LL t) {
	if (t == 1) return g;
	vector<vector<LL>> temp = pow(g, t / 2);
	vector<vector<LL>> temp1 = multiple(temp, temp);
	if (t % 2 == 0) return temp1;
	return multiple(temp1, g);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> S >> E >> T; string s;
	--S; --E;
	for (int i = 0; i < N; ++i) {
		cin >> s;
		for (int j = 0; j < 4; ++j) graph[5 * i + j + 1][5 * i + j] = 1;
		for (int j = 0; j < N; ++j) {
			if (s[j] != '0') graph[5 * i][5 * j + s[j] - '1'] = 1;
		}
	}
	vector<vector<LL>> ans = pow(graph, T);
	cout << ans[S * 5][E * 5];
}