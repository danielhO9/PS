#include <bits/stdc++.h>
using namespace std;

void solve() {
	int a, b; cin >> a >> b;
	if (abs(a - b) % 2 == 0) {
		cout << "Bob\n"; return;
	}
	cout << "Alice\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}