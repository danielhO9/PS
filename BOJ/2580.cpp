#include <bits/stdc++.h>
using namespace std;

int sudoku[9][9];
bool r[9][10], c[9][10], g[9][10];
vector<pair<int, int>> z;
int ans[9][9];
bool getAns = false;

void backtracking(int ind) {
	if (getAns) return;
	if (ind == z.size()) {
		for (int i = 0; i < 9; ++i) for (int j = 0; j < 9; ++j) ans[i][j] = sudoku[i][j];
		getAns = true;
		return;
	}
	int y = z[ind].first, x = z[ind].second;
	for (int i = 1; i <= 9; ++i) {
		if (!r[y][i] && !c[x][i] && !g[(y / 3) * 3 + (x / 3)][i]) {
			r[y][i] = true; c[x][i] = true; g[(y / 3) * 3 + (x / 3)][i] = true; sudoku[y][x] = i;
			backtracking(ind + 1);
			r[y][i] = false; c[x][i] = false; g[(y / 3) * 3 + (x / 3)][i] = false; sudoku[y][x] = 0;
		}
	}
}

void solve() {
	for (int i = 0; i < 9; ++i) for (int j = 0; j < 9; ++j) {
		cin >> sudoku[i][j];
		if (sudoku[i][j] == 0) {
			z.push_back(make_pair(i, j));
			continue;
		}
		r[i][sudoku[i][j]] = true;
		c[j][sudoku[i][j]] = true;
		g[(i / 3) * 3 + (j / 3)][sudoku[i][j]] = true;
	}
	backtracking(0);
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) cout << ans[i][j] << ' ';
		cout << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}