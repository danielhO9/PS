#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int ans[1001];
	ans[0] = 0; ans[1] = 0;
	bool vis[1001];
	int N; cin >> N;
	for (int i = 2; i <= N; ++i) {
		memset(vis, 0, sizeof(vis));
		int sum = i - 2;
		for (int j = 0; j <= (i - 2) / 2; ++j) vis[ans[j] ^ ans[i - 2 - j]] = 1;
		for (int j = 0; j < 1000; ++j) if (!vis[j]) {
			ans[i] = j;
			break;
		}
	}
	if (ans[N] > 0) cout << 1;
	else cout << 2;
}