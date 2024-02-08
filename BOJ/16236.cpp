#include <bits/stdc++.h>
using namespace std;

int sea[20][20], N, big = 2, eat, ans, nd;
int dx[4] = {0, -1, 0, 1}, dy[4] = {-1, 0, 1, 0}, visited[20][20];
pair<int, int> shark, np;

bool available(int y, int x) {
	if (0 <= y && y < N && 0 <= x && x < N && sea[y][x] <= big && !visited[y][x]) return true;
	return false;
}

bool bfs() {
	memset(visited, 0, sizeof(visited));
	deque<pair<pair<int, int>, int>> Q;
	visited[shark.first][shark.second] = 1;
	Q.push_back({{shark.first, shark.second}, 0});
	bool avail = 0;
	pair<pair<int, int>, int> des;
	while (!Q.empty()) {
		np = Q.front().first; nd = Q.front().second;
		if ((avail && nd == des.second && sea[np.first][np.second] < big && sea[np.first][np.second] != 0) || (!avail && sea[np.first][np.second] < big && sea[np.first][np.second] != 0)) {
			if (!avail) {
				avail = 1;
				des.first.first = np.first; des.first.second = np.second;
				des.second = nd;
			}
			else if (des.first.first > np.first) { des.first.first = np.first; des.first.second = np.second; }
			else if (des.first.first == np.first && des.first.second > np.second) { des.first.first = np.first; des.first.second = np.second; }
		} else if (!avail) {
			for (int i = 0; i < 4; ++i) if (available(np.first + dy[i], np.second + dx[i])) {
				Q.push_back({{np.first + dy[i], np.second + dx[i]}, nd + 1});
				visited[np.first + dy[i]][np.second + dx[i]] = 1;
			}	
		}
		Q.pop_front();
	}
	if (!avail) return false;
	ans += des.second; sea[des.first.first][des.first.second] = 0;
	shark.first = des.first.first; shark.second = des.first.second;
	++eat; if (eat == big) { eat = 0; ++big; }
	return true;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
		cin >> sea[i][j];
		if (sea[i][j] == 9) {
			shark.first = i; shark.second = j;
			sea[i][j] = 0;
		}
	}
	while (bfs());
	
	cout << ans;
}