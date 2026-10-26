#include <bits/stdc++.h>
using namespace std;

int n; string s;

int solution() {
	cin >> n; cin >> s;
	int cnt = 0, maxc = 0, sum = 0;
	for (auto i: s) {
		if (i == '.') {
			++cnt; maxc = max(maxc, cnt);
			++sum;
		}
		else cnt = 0;
	}
	if (maxc > 2) return 2;
	return sum;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) cout << solution() << '\n';
}