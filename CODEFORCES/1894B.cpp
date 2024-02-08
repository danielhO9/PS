#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	int a[n];
	for (int i = 0; i < n; ++i) cin >> a[i];
	int cnt[101];
	for (int i = 1; i <= 100; ++i) cnt[i] = 0;
	for (int i = 0; i < n; ++i) ++cnt[a[i]];
	vector<int> temp;
	for (int i = 1; i <= 100; ++i) {
		if (cnt[i] >= 2 && temp.size() < 2) temp.push_back(i);
	}
	if (temp.size() < 2) {
		cout << -1 << '\n';
		return;
	}
	bool visited[2]; visited[0] = 0; visited[1] = 0;
	for (int i = 0; i < n; ++i) {
		if (a[i] == temp[0] && !visited[0]) {
			cout << 2 << ' ';
			visited[0] = 1;
		}
		else if (a[i] == temp[1] && !visited[1]) {
			cout << 3 << ' ';
			visited[1] = 1;
		}
		else cout << 1 << ' ';
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}