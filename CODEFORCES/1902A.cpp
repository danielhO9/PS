#include <bits/stdc++.h>
using namespace std;

int n; string s;

void solution() {
	cin >> n >> s;
	for (auto i: s) if (i == '0') {
		cout << "YES" << '\n';
		return;
	}
	cout << "NO" << '\n';
	return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solution();
}