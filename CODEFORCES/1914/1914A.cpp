#include <bits/stdc++.h>
using namespace std;

void solution() {
	int n; cin >> n;
	string s; cin >> s;
	int cnt[26];
	for (int i = 0; i < 26; ++i) cnt[i] = 0;
	for (auto i: s) {
		++cnt[i - 'A'];
	}
	int ans = 0;
	for (int i = 0; i < 26; ++i) {
		if (cnt[i] >= i + 1) ++ans;
	}
	cout << ans << '\n';
	return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solution();
}