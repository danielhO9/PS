#include <bits/stdc++.h>
using namespace std;

int S;
int vis[4000];

void init() {
	for (int i = 0; i < 4000; ++i) vis[i] = 987654321;
	vis[1] = 0;
	for (int i = 1; i < 4000; ++i) {
		int cnt = 1;
		for (int j = i * 2; j < 4000; j += i) {
			vis[j] = min(vis[j], (++cnt) + vis[i]);
		}
		for (int i = 4000-1; i > 0; --i) vis[i - 1] = min(vis[i - 1], vis[i] + 1);
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	init();
	cin >> S;
	cout << vis[S];
}