#include <bits/stdc++.h>
using namespace std;

int cache[100][100];

void solve() {
	string a, b; cin >> a >> b;
	
	for (int i = 0; i < a.size(); ++i) {
		for (int j = 0; j < b.size(); ++j) {

			if (i == 0) {
				if (j == 0) cache[i][j] = a[i] == b[j] ? 1 : 2;
				else {
					cache[i][j]= cache[i][j - 1] + 1;
					if (a[i] == b[j]) cache[i][j] = min(cache[i][j], j + 1);
				}
			} else {
				if (j == 0) {
					cache[i][j] = cache[i - 1][j] + 1;
					if (a[i] == b[j]) cache[i][j] = min(cache[i][j], i + 1);
				} else {
					cache[i][j] = min(cache[i - 1][j], cache[i][j - 1]) + 1;
					if (a[i] == b[j]) cache[i][j] = min(cache[i - 1][j - 1] + 1, cache[i][j]);
				}
			}

		}
	}
	cout << cache[(int)a.size() - 1][(int)b.size() - 1] << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}