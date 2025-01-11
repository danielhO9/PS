#include <bits/stdc++.h>
using namespace std;

int k, w;

void solve() {
	cin >> k >> w;
	string ans;
	for (int i = 0; i < w; ++i) {
		string s; cin >> s;
		int cur = -1;
		for (int j = k - 1; j >= 0; --j) if (ans.size() >= j + 1) {
			bool flag = true;
			for (int l = 0; l <= j; ++l) if (ans[(int)ans.size() - (j + 1) + l] != s[l]) {
				flag = false;
				break;
			}
			if (flag) {
				cur = j;
				break;
			}
		}
		for (int l = cur + 1; l < k; ++l) ans.push_back(s[l]);
	}
	cout << ans.size() << '\n';

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}