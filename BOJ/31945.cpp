#include <bits/stdc++.h>
using namespace std;

int P[8][3] = {
	{0, 0, 0},
	{0, 0, 1},
	{0, 1, 0},
	{0, 1, 1},
	{1, 0, 0},
	{1, 0, 1},
	{1, 1, 0},
	{1, 1, 1}
};

void solve() {
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	for (int i = 0; i < 3; ++i) {
		if (P[a][i] == P[b][i] && P[b][i] == P[c][i] && P[c][i] == P[d][i]) {
			cout << "YES\n";
			return;
		}
	}
	cout << "NO\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}