#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int ans = 0;
	for (int i = 0; i < 12; ++i) {
		string s; cin >> s;
		if (s.size() == i + 1) ++ans;
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}