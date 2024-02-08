#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	int n; cin >> n;
	LL cache[6][6][46][46];
	memset(cache, 0, sizeof(cache));
	string s[n];
	for (int i = 0; i < n; ++i) {
		cin >> s[i];
		int fs = 0, sum = 0;
		for (auto j: s[i]) sum += j - '0';
		for (int j = 0; j <= s[i].length(); ++j) {
			if (j > 0) {
				fs += s[i][j - 1] - '0';
				sum -= s[i][j - 1] - '0';
			}
			++cache[j][(int)s[i].length() - j][fs][sum];
		}
	}
	LL ans = 0;
	for (int i = 0; i < n; ++i) {
		int sum = 0; int l = s[i].length();
		for (auto j: s[i]) sum += j - '0';
		for (int j = sum; j <= 45; ++j) {
			for (int k = 0; k <= 5; ++k) {
				if (l + 2 * k > 5) break;
				ans += cache[k][l + k][j - sum][j];
			}
		}
		for (int j = sum; j <= 45; ++j) {
			for (int k = 0; k <= 5; ++k) {
				if (l + 2 * k > 5) break;
				ans += cache[l + k][k][j][j - sum];
			}
		}
		ans -= cache[l][0][sum][0];
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}