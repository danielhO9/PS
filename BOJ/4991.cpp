#include <bits/stdc++.h>
using namespace std;

int h, w, src;
char room[20][20];
int dis[20][20];
vector<int> dirt;
int ndis[10][10];
int dy[4] = {1, -1, 0, 0}, dx[4] = {0, 0, 1, -1};
int cache[1 << 10][10];
int MAX = 987654321;

int matchCache(int mask, int here) {
	int& ret = cache[mask][here];
	if (ret != -1) return ret;
	ret = MAX;
	for (int i = 0; i < dirt.size(); ++i) if ((mask >> i) & 1) {
		ret = min(ret, matchCache(mask ^ (1 << i), i) + ndis[i][here]);
	}
	return ret;
}

void solve() {
	dirt.clear(); memset(cache, -1, sizeof(cache));
	for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j) {
		cin >> room[i][j];
		if (room[i][j] == '*') dirt.push_back(i * w + j);
		if (room[i][j] == 'o') src = i * w + j;
	}
	for (int i = 0; i < dirt.size(); ++i) {
		for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j) dis[i][j] = MAX;
		queue<int> Q; Q.push({dirt[i]});
		dis[dirt[i] / w][dirt[i] % w] = 0;
		while (!Q.empty()) {
			int here = Q.front(); Q.pop();
			int y = here / w, x = here % w;
			for (int j = 0; j < 4; ++j) {
				int ny = y + dy[j], nx = x + dx[j];
				if (0 <= ny && ny < h && 0 <= nx && nx < w && room[ny][nx] != 'x' && dis[ny][nx] == MAX) {
					Q.push(ny * w + nx);
					dis[ny][nx] = dis[y][x] + 1;
				}
			}
		}
		for (int j = 0; j < dirt.size(); ++j) ndis[i][j] = dis[dirt[j] / w][dirt[j] % w];
	}
	for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j) dis[i][j] = MAX;
	queue<int> Q; Q.push({src});
	dis[src / w][src % w] = 0;
	while (!Q.empty()) {
		int here = Q.front(); Q.pop();
		int y = here / w, x = here % w;
		for (int j = 0; j < 4; ++j) {
			int ny = y + dy[j], nx = x + dx[j];
			if (0 <= ny && ny < h && 0 <= nx && nx < w && room[ny][nx] != 'x' && dis[ny][nx] == MAX) {
				Q.push(ny * w + nx);
				dis[ny][nx] = dis[y][x] + 1;
			}
		}
	}
	for (int j = 0; j < dirt.size(); ++j) cache[0][j] = dis[dirt[j] / w][dirt[j] % w];
	int ans = MAX;
	for (int i = 0; i < dirt.size(); ++i) {
		int tmp = (1 << (dirt.size())) - 1;
		ans = min(ans, matchCache(tmp ^ (1 << i), i));
	}
	if (ans == MAX) cout << "-1\n";
	else cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	while (true) {
		cin >> w >> h;
		if (w == 0 && h == 0) break;
		solve();
	}
}