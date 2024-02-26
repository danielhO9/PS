#include <bits/stdc++.h>
using namespace std;
int k;

vector<vector<int>> rotate(const vector<vector<int>>& field) {
	vector<vector<int>> ret(field[0].size(), vector<int>(field.size()));
	for (int i = 0; i < field.size(); ++i) {
		for (int j = 0; j < field[i].size(); ++j) {
			ret[j][(int) field.size() - 1 - i] = field[i][j];
		}
	}
	return ret;
}

int getAns(const vector<vector<int>>& field) {
	vector<vector<int>> sum(field.size(), vector<int>(field[0].size(), 0));
	vector<vector<int>> dsum(field.size(), vector<int>(field[0].size(), 0));
	for (int i = 0; i < field.size(); ++i) {
		for (int j = 0; j < field[i].size(); ++j) {
			if (i == 0) {
				sum[i][j] = field[i][j];
				dsum[i][j] = field[i][j];
			}
			else {
				sum[i][j] = sum[i - 1][j] + field[i][j];
				dsum[i][j] = field[i][j];
				if (j + 1 < field[i].size()) dsum[i][j] += dsum[i - 1][j + 1];
			}
		}
	}
	int ret = 0;
	vector<vector<int>> ans(field.size(), vector<int>(field[0].size(), 0));
	for (int i = 0; i < field.size(); ++i) {
		for (int j = 0; j < field[i].size(); ++j) {
			if (j == 0) {
				ans[i][j] = sum[i][j];
				if (i - k >= 0) ans[i][j] -= sum[i - k][j];
			} else {
				ans[i][j] = ans[i][j - 1] + sum[i][j];
				if (i - k >= 0) ans[i][j] -= sum[i - k][j];
				ans[i][j] -= j - k >= 0 ? dsum[i][j - k] : i + j - k >= 0 ? dsum[i + j - k][0] : 0;
				ans[i][j] += i - k >= 0 ? dsum[i - k][j] : 0;
			}
			ret = max(ret, ans[i][j]);
		}
	}
	return ret;
}

void solve() {
	int n, m; cin >> n >> m >> k; ++k;
	vector<vector<int>> field(n, vector<int>(m, 0));
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
		char c; cin >> c;
		if (c == '#') field[i][j] = 1;
		else field[i][j] = 0;
	}
	int ans = 0;
	for (int i = 0; i < 4; ++i) {
		field = rotate(field);
		ans = max(ans, getAns(field));
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}