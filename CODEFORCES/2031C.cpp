#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;

void solve() {
	cin >> n;
	if (n % 2 == 0) {
		for (int i = 1; i <= n / 2; ++i) cout << i << ' ' << i << ' ';
		cout << '\n';
		return;
	} else {
		if (n < 27) {
			cout << -1 << '\n';
			return;
		}
		vector<int> ans(n + 1, 0);
		ans[1] = 1; ans[10] = 1; ans[26] = 1;
		ans[27] = 2; ans[23] = 2;
		int cur = 1;
		for (int i = 3; i <= (n - 1) / 2; ++i) {
			while (ans[cur] != 0) ++cur;
			ans[cur] = i; ++cur;
			while (ans[cur] != 0) ++cur;
			ans[cur] = i; ++cur;
		}
		for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
		cout << '\n';
	}

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}