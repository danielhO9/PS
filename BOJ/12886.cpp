#include <bits/stdc++.h>
using namespace std;

bool vis[1501][1501];
vector<int> tmp;

void solve() {
	memset(vis, 0, sizeof(vis));
	int A, B, C; cin >> A >> B >> C;
	if ((A + B + C) % 3 != 0) {
		cout << 0; return;
	}
	if (A > B) swap(A, B);
	if (B > C) swap(B, C);
	if (A > B) swap(A, B);
	queue<pair<int, int>> Q;
	vis[A][B] = true; Q.push({A, B});
	while (!Q.empty()) {
		auto [a, b] = Q.front(); Q.pop();
		int c = A + B + C - a - b;
		tmp = {a + a, b - a, c};
		sort(tmp.begin(), tmp.end());
		if (!vis[tmp[0]][tmp[1]]) {
			Q.push({tmp[0], tmp[1]});
			vis[tmp[0]][tmp[1]] = true;
		}
		tmp = {a, b + b, c - b};
		sort(tmp.begin(), tmp.end());
		if (!vis[tmp[0]][tmp[1]]) {
			Q.push({tmp[0], tmp[1]});
			vis[tmp[0]][tmp[1]] = true;
		}
		tmp = {a + a, b, c - a};
		sort(tmp.begin(), tmp.end());
		if (!vis[tmp[0]][tmp[1]]) {
			Q.push({tmp[0], tmp[1]});
			vis[tmp[0]][tmp[1]] = true;
		}
	}
	cout << vis[(A + B + C) / 3][(A + B + C) / 3];
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}