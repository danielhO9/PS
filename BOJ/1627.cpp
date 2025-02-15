#include <bits/stdc++.h>
using namespace std;

// P.P, PP. -> 0
// ..P.. next : always 0 -> 1

int N;
int board[3000];
int grundy[3001];
bool vis[3001];
bool pos[3001];

void init() {
	grundy[0] = 0;
	grundy[1] = 1; // . . . -> . P .
	grundy[2] = 1; // . .. . -> . .P .
	for (int i = 3; i <= 3000; ++i) {
		memset(vis, 0, sizeof(vis));
		for (int j = 1; j <= i; ++j) {
			int l = max(0, j - 3);
			int r = max(0, i - j - 2);
			int val = grundy[l] ^ grundy[r];
			if (val <= 3000) vis[val] = true;
		}
		for (int j = 0; j <= 3000; ++j) if (!vis[j]) {
			grundy[i] = j;
			// cout << i << ' ' << j << '\n';
			break;
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	init();
	cin >> N;
	string s; cin >> s; for (int i = 0; i < N; ++i) board[i] = (s[i] == 'P');
	vector<int> ans;
	for (int i = 0; i < N; ++i) if (!board[i]) {
		bool flag = false;
		if (i + 2 < N && board[i + 1] && board[i + 2]) flag = true;
		if (i + 1 < N && i - 1 >= 0 && board[i + 1] && board[i - 1]) flag = true;
		if (i - 2 >= 0 && i - 1 >= 0 && board[i - 2] && board[i - 1]) flag = true;
		if (flag) ans.push_back(i);
	}
	if (!ans.empty()) {
		cout << "WINNING\n";
		for (auto i: ans) cout << i + 1 << ' ';
		return 0;
	}

	for (int i = 0; i < N; ++i) if (board[i]) {
		for (int j = -2; j <= 2; ++j) {
			int ni = i + j;
			if (0 <= ni && ni < N) pos[ni] = true;
		}
	}
	vector<pair<int, int>> gs;
	int cnt = 0;
	for (int i = 0; i < N; ++i) {
		if (pos[i]) {
			if (cnt != 0) gs.push_back({i - cnt, cnt});
			cnt = 0;
		} else ++cnt;
	}
	if (cnt != 0) gs.push_back({N - cnt, cnt});
	if (gs.empty()) {
		cout << "LOSING";
		return 0;
	}
	// for (int i = 1; i <= 5; ++i) cout << grundy[i] << ' ';
	// cout << '\n';
	for (int i = 0; i < gs.size(); ++i) {
		int prv = 0;
		for (int j = 0; j < gs.size(); ++j) if (j != i) prv ^= grundy[gs[j].second];
		for (int j = gs[i].first; j < gs[i].first + gs[i].second; ++j) {
			int len = gs[i].second;
			int idx = j - gs[i].first + 1;
			int l = max(0, idx - 3);
			int r = max(0, len - idx - 2);
			int val = grundy[l] ^ grundy[r];
			if ((val ^ prv) == 0) ans.push_back(j);
		}
	}
	if (ans.empty()) cout << "LOSING";
	else {
		cout << "WINNING\n";
		for (auto i: ans) cout << i + 1 << ' ';
	}
}