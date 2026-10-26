#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int n;
LL a[200000], b[200000];

void solution() {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < n; ++i) cin >> b[i];
	priority_queue<pair<LL, int>> Q;
	for (int i = 0; i < n; ++i) {
		Q.push({a[i] + b[i], i});
	}
	LL ans = 0; int turn = 0; pair<LL, int> p;
	while (!Q.empty()) {
		p = Q.top();
		Q.pop();
		if (turn % 2 == 0) ans += (a[p.second] - 1);
		else ans -= (b[p.second] - 1);
		++turn;
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solution();
}