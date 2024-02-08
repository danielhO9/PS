#include <bits/stdc++.h>
using namespace std;

int R, C, ans, visited[26], dy[4] = {0, 1, 0, -1}, dx[4] = {1, 0, -1, 0};
char board[20][20];

void solution(int y, int x, int n) {
	ans = max(ans, n);
	for (int i = 0; i < 4; ++i) {
		if (0 <= y + dy[i] && y + dy[i] < R && 0 <= x + dx[i] && x + dx[i] < C
		&& visited[board[y + dy[i]][x + dx[i]] - 'A'] == 0) {
			visited[board[y + dy[i]][x + dx[i]] - 'A'] = 1;
			solution(y + dy[i], x + dx[i], n + 1);
			visited[board[y + dy[i]][x + dx[i]] - 'A'] = 0;
		}	
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> R >> C; string temp;
	for (int i = 0; i < R; ++i) {
		cin >> temp;
		for (int j = 0; j < C; ++j) board[i][j] = temp[j];
	}
	visited[board[0][0] - 'A'] = 1;
	solution(0, 0, 1);
	cout << ans;
}