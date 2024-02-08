#include <bits/stdc++.h>
using namespace std;

int bino[201][201], n, m, k;

void calcBino() {
	for (int i = 0; i <= 200; ++i) {
		bino[i][0] = bino[i][i] = 1;
		for (int j = 1; j < i; ++j) bino[i][j] = min((int) 1e9 + 1, bino[i - 1][j - 1] + bino[i - 1][j]);
	}
}

string kth(int n, int m, int skip) {
	if (n == 0) return string(m, 'o');
	if (skip < bino[n +m - 1][n - 1]) return "-" + kth(n - 1, m, skip);
	return "o" + kth(n, m - 1, skip - bino[n + m - 1][n - 1]);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int C; cin >> C;
	calcBino();
	for (int i = 0; i < C; ++i) {
		cin >> n >> m >> k;
		cout << kth(n, m, k - 1) << "\n";
	}
}