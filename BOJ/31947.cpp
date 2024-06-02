#include <bits/stdc++.h>
using namespace std;

double pos[10001][500];
int N, M, S, E;

void solve() {
	cin >> N >> M >> S >> E;
	pos[0][S - 1] = 1.0;
	for (int i = 1; i <= M; ++i) {
		for (int j = 0; j < N; ++j) {
			if (j == 0) {
				pos[i][j] += pos[i - 1][j] / (N - 1) * (N - 2);
				pos[i][j] += pos[i - 1][j + 1] / (N - 1);
			} else if (j == N - 1) {
				pos[i][j] += pos[i - 1][j] / (N - 1) * (N - 2);
				pos[i][j] += pos[i - 1][j - 1] / (N - 1);
			} else {
				pos[i][j] += pos[i - 1][j] / (N - 1) * (N - 3);
				pos[i][j] += pos[i - 1][j + 1] / (N - 1);
				pos[i][j] += pos[i - 1][j - 1] / (N - 1);
			}
		}
	}
	
	cout << fixed;
	cout.precision(7);
	cout << pos[M][E - 1];
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}

/*
2 1000
1 1
*/