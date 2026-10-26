#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, m;
bool b[500][500];

void solve() {
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		string tmp; cin >> tmp;
		for (int j = 0; j < m; ++j) b[i][j] = (tmp[j] == 'B');
	}
	if (b[0][0] == b[n - 1][m - 1] || b[n - 1][0] == b[0][m - 1]) {
		cout << "YES\n"; return;
	} 
	if (b[0][0] == b[0][m - 1]) {
		for (int i = 0; i < m; ++i) {
			if (b[n - 1][i] == b[0][0]) {
				cout << "YES\n"; return;
			}
			if (b[0][i] == b[n - 1][0]) {
				cout << "YES\n"; return;
			}
		}
		cout << "NO\n";
		return;
	}
	for (int i = 0; i < n; ++i) {
		if (b[i][m - 1] == b[0][0]) {
			cout << "YES\n"; return;
		}
		if (b[i][0] == b[0][m - 1]) {
			cout << "YES\n"; return;
		}
	}
	cout << "NO\n";
	return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}