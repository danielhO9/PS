#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 10000;
int n, e[MAX_N], m[MAX_N];

int heat() {
	vector<pair<int, int>> order;
	for (int i = 0; i < n; ++i) order.push_back(make_pair(-e[i], i));
	sort(order.begin(), order.end());
	int ret = 0, beginEat = 0;
	for (int i = 0; i < n; ++i) {
		int box = order[i].second;
		beginEat += m[box];
		ret = max(ret, beginEat + e[box]);
	}
	return ret;
}

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> m[i];
	for (int i = 0; i < n; ++i) cin >> e[i];
	cout << heat() << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}