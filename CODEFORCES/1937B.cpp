#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	ll n; cin >> n;
	vector<vector<ll>> grid(2, vector<ll>(n, 0));
	for (int i = 0; i < n; ++i) {
		char c; cin >> c;
		if (c == '0') grid[0][i] = 0;
		else grid[0][i] = 1;
	}
	for (int i = 0; i < n; ++i) {
		char c; cin >> c;
		if (c == '0') grid[1][i] = 0;
		else grid[1][i] = 1;
	}
	vector<int> V;
	ll y = 0;
	for (int i = 0; i < n; ++i) {
		if (i == n - 1) {
			if (y == 0) {
				V.push_back(grid[0][i]);
				V.push_back(grid[1][i]);
			} else {
				V.push_back(grid[1][i]);
			}
		} else {
			if (y == 1) V.push_back(grid[1][i]);
			else {
				if (grid[1][i] == 0 && grid[0][i + 1] == 1) {
					V.push_back(grid[0][i]);
					V.push_back(grid[1][i]);
					y = 1;
				} else {
					V.push_back(grid[0][i]);
				}
			}
		}
	}
	for (auto i: V) cout << i;
	cout << '\n';
	int l, r;
	for (int i = 0; i < n; ++i) {
		if (V[i] == grid[0][i]) l = i;
		else break;
	}
	for (int i = n - 1; i >= 0; --i) {
		if (V[i + 1] == grid[1][i]) r = i;
		else break;
	}
	cout << l - r + 1 << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}