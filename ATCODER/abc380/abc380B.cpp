#include <bits/stdc++.h>
using namespace std;

void solve() {
	string s; cin >> s;
	vector<int> ans;
	int cnt = 0;
	for (auto i: s) {
		if (i == '|') {
			if (cnt != 0) ans.push_back(cnt);
			cnt = 0;
		} else {
			++cnt;
		}
	}
	for (auto i: ans) cout << i << ' ';
	
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}