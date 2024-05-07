#include <bits/stdc++.h>
using namespace std;

int N;
int board[9][9], ans[9][9];
bool used[10][10];
int row[9], col[9], grid[3][3];
int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, 1, -1};
bool done = false;

void add(int i, int j, int num) {
	board[i][j] = num;
	row[i] ^= (1 << num);
	col[j] ^= (1 << num);
	grid[i / 3][j / 3] ^= (1 << num);
}

void del(int i, int j, int num) {
	board[i][j] = 0;
	row[i] ^= (1 << num);
	col[j] ^= (1 << num);
	grid[i / 3][j / 3] ^= (1 << num);
}

bool pos(int i, int j, int num) {
	if ((row[i] >> num) & 1) return false;
	if ((col[j] >> num) & 1) return false;
	if ((grid[i / 3][j / 3] >> num) & 1) return false;
	return true;
}

void dfs(int y, int x) {
	if (done) return;
	if (y == 9) {
		for (int i = 0; i < 9; ++i) for (int j = 0; j < 9; ++j) ans[i][j] = board[i][j];
		done = true;
		return;
	}
	int nx = (x + 1) % 9;
	int ny = nx == 0 ? y + 1 : y;
	if (board[y][x] != 0) {
		dfs(ny, nx);
		return;
	}
	for (int i = 0; i < 4; ++i) {
		int sy = y + dy[i], sx = x + dx[i];
		if (board[sy][sx] == 0) {
			// (y, x), (sy, sx)
			for (int f = 1; f <= 9; ++f) if (pos(y, x, f)) {
				for (int s = 1; s <= 9; ++s) {
					if (s != f && pos(sy, sx, s) && !used[f][s]) {
						add(y, x, f), add(sy, sx, s);
						used[f][s] = true, used[s][f] = true;
						dfs(ny, nx);
						del(y, x, f), del(sy, sx, s);
						used[f][s] = false, used[s][f] = false;
					}
				}
			}
		}
	}
}

void solve() {
	done = false;
	memset(board, 0, sizeof(board));
	memset(used, 0, sizeof(used));
	memset(row, 0, sizeof(row));
	memset(col, 0, sizeof(col));
	memset(grid, 0, sizeof(grid));
	for (int i = 0; i < N; ++i) {
		int U, V;
		string LU, LV;
		cin >> U >> LU >> V >> LV;
		add(LU[0] - 'A', LU[1] - '1', U);
		add(LV[0] - 'A', LV[1] - '1', V);
		used[U][V] = true;
		used[V][U] = true;
	}
	for (int i = 1; i <= 9; ++i) {
		string LU; cin >> LU;
		add(LU[0] - 'A', LU[1] - '1', i);
	}
	dfs(0, 0);
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) cout << ans[i][j];
		cout << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int cnt = 0;
	while (true) {
		cin >> N;
		if (N == 0) break;
		++cnt;
		cout << "Puzzle "<< cnt << '\n';
		solve();
	}
}