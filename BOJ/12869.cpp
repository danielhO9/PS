#include <bits/stdc++.h>
using namespace std;

int cache[61][61][61];
vector<int> ord[6] = {
	{0, 1, 2},
	{0, 2, 1},
	{1, 0, 2},
	{1, 2, 0},
	{2, 0, 1},
	{2, 1, 0}
};
int attack[3] = {9, 3, 1};

void solve() {
	memset(cache, -1, sizeof(cache));
	int N; cin >> N;
	vector<int> health;
	for (int i = 0; i < N; ++i) {
		int tmp; cin >> tmp;
		health.push_back(tmp);
	}
	while (health.size() < 3) health.push_back(0);
	sort(health.begin(), health.end());
	cache[health[0]][health[1]][health[2]] = 0;
	queue<vector<int>> Q; Q.push(health);
	while (!Q.empty()) {
		vector<int> here = Q.front(); Q.pop();
		for (int i = 0; i < 6; ++i) {
			vector<int> tmp = here;
			for (int j = 0; j < 3; ++j) tmp[j] = max(0, tmp[j] - attack[ord[i][j]]);
			sort(tmp.begin(), tmp.end());
			if (cache[tmp[0]][tmp[1]][tmp[2]] == -1) {
				cache[tmp[0]][tmp[1]][tmp[2]] = cache[here[0]][here[1]][here[2]] + 1;
				Q.push(tmp);
			}
		}
	}
	cout << cache[0][0][0];
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}