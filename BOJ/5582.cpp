#include <bits/stdc++.h>
using namespace std;

string p, q;
int cache[4000][4000];

void solve() {
	cin >> p;
	cin >> q;
	int ans = 0;
	for (int i = 0; i < p.size(); ++i) for (int j = 0; j < q.size(); ++j) {
		if (i == 0 || j == 0) {
			if (p[i] == q[j]) cache[i][j] = 1;
			else cache[i][j] = 0;
			ans = max(ans, cache[i][j]);
			continue;
		}
		if (p[i] == q[j]) cache[i][j] = cache[i - 1][j - 1] + 1;
		else cache[i][j] = 0;
		ans = max(ans, cache[i][j]);
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}