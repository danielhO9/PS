#include <bits/stdc++.h>
using namespace std;

int n, sx, sy, x[100000], y[100000];

void solution() {
	cin >> n;
	cin >> sx >> sy;
	int v = (sx % 2) ^ (sy % 2);
	set<int> p[2];
	for (int i = 0; i < n; ++i) {
		cin >> x[i] >> y[i];
		p[(x[i] % 2) ^ (y[i] % 2)].insert(i + 1);
	}
	if (p[v].size() >= p[1 - v].size()) {
		cout << "First" << endl;
		v = 1 - v;
		for (int i = 0; i < n; ++i) {
			if (i % 2 == 0) {
				int j;
				if (!p[v].empty()) {
					j = (*p[v].begin());
					p[v].erase(j);
				} else {
					j = (*p[1 - v].begin());
					p[1 - v].erase(j);
				}
				cout << j << endl;
			} else {
				int j; cin >> j;
				if (p[0].count(j)) p[0].erase(j);
				else p[1].erase(j);
			}
		}
	} else {
		cout << "Second" << endl;
		for (int i = 0; i < n; ++i) {
			if (i % 2 == 1) {
				int j;
				if (!p[v].empty()) {
					j = (*p[v].begin());
					p[v].erase(j);
				} else {
					j = (*p[1 - v].begin());
					p[1 - v].erase(j);
				}
				cout << j << endl;
			} else {
				int j; cin >> j;
				if (p[0].count(j)) p[0].erase(j);
				else p[1].erase(j);
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solution();
}