#include <bits/stdc++.h>
using namespace std;

int n;
char matrix[11][11];
vector<int> sum = {0};
vector<int> ans;

void generator() {
	if (!ans.empty()) return;
	if (sum.size() == n + 1) {
		ans = sum;
		return;
	}
	int m = sum.size();
	for (int i = sum.back() - 10; i <= sum.back() + 10; ++i) {
		sum.push_back(i);
		bool flag = true;
		for (int j = 1; j <= m; ++j) {
			if ((matrix[j][m] == '+' && sum[m] - sum[j - 1] <= 0)
			|| (matrix[j][m] == '0' && sum[m] - sum[j - 1] != 0)
			|| (matrix[j][m] == '-' && sum[m] - sum[j - 1] >= 0)) {
				flag = false;
				break;
			}
		}
		if (flag) generator();
		sum.pop_back();
	}
}

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) for (int j = i; j <= n; ++j) cin >> matrix[i][j];
	generator();
	for (int i = 1; i <= n; ++i) {
		cout << ans[i] - ans[i - 1] << ' ';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}