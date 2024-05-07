#include <bits/stdc++.h>
using namespace std;

int field[6][6];

int dy[4] = {0, 0, 1, -1};
int dx[4] = {1, -1, 0, 0};

void solve() {
	for (int i = 0; i < 6; ++i) for (int j = 0; j < 6; ++j) cin >> field[i][j];
	for (int i = 0; i < 6; ++i) for (int j = 0; j < 6; ++j) if (field[i][j]) {
		field[i][j] = 2;
		deque<pair<pair<int, int>, int>> Q;
		for (int k = 0; k < 4; ++k) {
			int ny = i + dy[k], nx = j + dx[k];
			if (0 <= ny && ny < 6 && 0 <= nx && nx < 6 && field[ny][nx] == 1) {
				Q.push_back({{ny, nx}, k});
				field[ny][nx] = 2;
			}
		}
		int cnt = 0;
		while (!Q.empty()) {
			auto here = Q.front(); Q.pop_front();
			for (int k = 0; k < 4; ++k) {
				int ny = here.first.first + dy[k], nx = here.first.second + dx[k];
				if (0 <= ny && ny < 6 && 0 <= nx && nx < 6 && field[ny][nx] == 1) {
					if (here.second == k) {
						++cnt;
						continue;
					}
					Q.push_back({{ny, nx}, here.second});
					field[ny][nx] = 2;
				}
			}
		}
		if (cnt != 1) {
			cout << "no\n";
			return;
		}
		for (int m = 0; m < 6; ++m) for (int n = 0; n < 6; ++n) if (field[m][n] == 2) field[m][n] = 1;
	}
	cout << "yes\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	for (int i = 0; i < 3; ++i) solve();
}