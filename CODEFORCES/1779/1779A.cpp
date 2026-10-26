#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
string s;

void solve() {
	cin >> N >> s;
	for (int i = 0; i + 1 < N; ++i) if (s[i] == 'L' && s[i + 1] == 'R') {
		cout << i + 1 << '\n';
		return;
	}
	for (int i = 0; i + 1 < N; ++i) if (s[i] == 'R' && s[i + 1] == 'L') {
		cout << 0 << '\n';
		return;
	}
	cout << -1 << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}