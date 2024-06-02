#include <bits/stdc++.h>
using namespace std;

int N, M, K;
bool virus[1001];
vector<vector<int>> todo;
bool ans[1001];

void solve() {
	cin >> N >> M >> K;
	memset(ans, false, sizeof(ans));
	for (int i = 0; i < K; ++i) {
		int t; cin >> t;
		ans[t] = true;
	}
	for (int i = 0; i < M; ++i) {
		int t, a, b; cin >> t >> a >> b;
		todo.push_back({t, a, b});
	}
	sort(todo.begin(), todo.end());
	for (int i = 1; i <= N; ++i) {
		memset(virus, 0, sizeof(virus));
		virus[i] = true;
		for (auto j: todo) {
			if (virus[j[1]]) virus[j[2]] = true;
		}
		bool flag = true;
		for (int j = 1; j <= N; ++j) {
			if (ans[j] != virus[j]) {
				flag = false;
				break;
			}
		}
		if (flag) {
			cout << i;
			return;
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}