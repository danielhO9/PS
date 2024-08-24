#include <bits/stdc++.h>
using namespace std;

int R, C;
int land[1000][1000];
char way[4] = {'R', 'D', 'L', 'U'};
int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0};
int miny, minx, minv;

bool inLand(int y, int x) {
	return (0 <= y && y < R && 0 <= x && x < C);
}

void solve() {
	cin >> R >> C;
	for (int i = 0; i < R; ++i) for (int j = 0; j < C; ++j) cin >> land[i][j];
	if (R % 2 || C % 2) {
		int sw;
		if (R % 2) sw = 0;
		else sw = 1;
		int pas;
		if (R % 2) pas = 1;
		else pas = 0;
		int y = 0, x = 0;
		while (y != R - 1 || x != C - 1) {
			while (inLand(y + dy[sw], x + dx[sw])) {
				y = y + dy[sw];
				x = x + dx[sw];
				cout << way[sw];
			}
			if (y != R - 1 || x != C - 1) {
				y = y + dy[pas];
				x = x + dx[pas];
				cout << way[pas];
			}
			sw += 2; sw %= 4;
		}
		return;
	}
	minv = 1000;
	for (int i = 0; i < R; ++i) for (int j = 0; j < C; ++j) if ((i + j) % 2) {
		if (minv > land[i][j]) {
			minv = land[i][j];
			miny = i;
			minx = j;
		}
	}
	int y = 0, x = 0;
	while (y != (miny / 2) * 2) {
		while (inLand(y + dy[0], x + dx[0])) {
			y = y + dy[0];
			x = x + dx[0];
			cout << way[0];
		}
		y = y + dy[1];
		x = x + dx[1];
		cout << way[1];
		while (inLand(y + dy[2], x + dx[2])) {
			y = y + dy[2];
			x = x + dx[2];
			cout << way[2];
		}
		y = y + dy[1];
		x = x + dx[1];
		cout << way[1];
	}
	vector<pair<int, int>> sldms = {{0, 1}, {0, 3}, {1, 0}, {3, 0}};
	int move = 2;
	bool flag = false;
	// cout << miny << ' ' << minx;
	while (y != miny / 2 * 2 + 1 || x != C - 1) {
		int ty = (y / 2 * 2) + 1 + (y / 2 * 2) - y;
		if (ty == miny && x == minx) {
			flag = true;
			if (y < ty) move = 0;
			else move = 1;
		}
		y = y + dy[sldms[move].first];
		x = x + dx[sldms[move].first];
		cout << way[sldms[move].first];
		y = y + dy[sldms[move].second];
		x = x + dx[sldms[move].second];
		cout << way[sldms[move].second];
		if (flag) move = 1 - move;
		else move = 5 - move;
	}

	while (y != R - 1 || x != C - 1) {
		y = y + dy[1];
		x = x + dx[1];
		cout << way[1];
		while (inLand(y + dy[2], x + dx[2])) {
			y = y + dy[2];
			x = x + dx[2];
			cout << way[2];
		}
		y = y + dy[1];
		x = x + dx[1];
		cout << way[1];
		while (inLand(y + dy[0], x + dx[0])) {
			y = y + dy[0];
			x = x + dx[0];
			cout << way[0];
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}

/*
5 1 3 1
2 4 8 2
1 1 2 3
4 5 6 7
*/