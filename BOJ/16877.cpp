#include <bits/stdc++.h>
using namespace std;

int grundy[3000001];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int a = 1, b = 2;
	vector<int> fibo; fibo.push_back(1); fibo.push_back(2);
	while (true) {
		if (fibo.back() > 3e6) break;
		fibo.push_back(a + b);
		a += b; swap(a, b);
	}
	int N; cin >> N;
	grundy[0] = 0;
	bool vis[33];
	for (int i = 1; i <= 3e6; ++i) {
		memset(vis, 0, sizeof(vis));
		for (int j: fibo) {
			if (i - j < 0) break;
			vis[grundy[i - j]] = 1;
		}
		for (int j = 0; j < 33; ++j) {
			if (!vis[j]) {
				grundy[i] = j;
				break;
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < N; ++i) {
		int P; cin >> P;
		ans ^= grundy[P];
	}
	if (ans > 0) cout << "koosaga";
	else cout << "cubelover";
}