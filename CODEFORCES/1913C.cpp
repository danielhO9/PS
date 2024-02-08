#include <bits/stdc++.h>
using namespace std;

int t, v, cnt[30];

void query1(int x) {
	++cnt[x];
	// for (int i = x; i < 29; ++i) {
	// 	if (cnt[i] <= 2) break;
	// 	cnt[i] = 1;
	// 	++cnt[i + 1];
	// }
}

void query2(int x) {
	for (int i = 29; i >= 0; --i) {
		int avail = min(cnt[i], x / (1 << i));
		x -= avail * (1 << i);
	}
	if (x == 0) cout << "YES" << '\n';
	else cout << "NO" << '\n';
	return;
}

void solution() {
	cin >> t >> v;
	if (t == 1) query1(v);
	else query2(v);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int m; cin >> m;
	while (m--) solution();
}

/*
5
1 0
1 0
1 0
2 3
2 0
*/