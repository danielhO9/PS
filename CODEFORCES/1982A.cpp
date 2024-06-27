#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int x1, y1; cin >> x1 >> y1;
	int x2, y2; cin >> x2 >> y2;
	if ((x1 <= y1 && y2 <= x2) || (y1 <= x1 && x2 <= y2)) {
		cout << "NO\n";
	} else cout << "YES\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}