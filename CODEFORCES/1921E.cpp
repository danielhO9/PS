#include <bits/stdc++.h>
using namespace std;

void solve() {
	int h, w, xa, ya, xb, yb; cin >> h >> w >> xa >> ya >> xb >> yb;
	if (xa > xb) { cout << "DRAW\n"; return; }
	if (abs(xa - xb) % 2 == 0) {
		if (ya < yb) {
			ya = max(1, ya - abs(xa - xb) / 2);
			yb = max(1, yb - abs(xa - xb) / 2 + 1);
			if (yb - ya <= 1) cout << "BOB\n";
			else cout << "DRAW\n";
		} else {
			ya = min(w, ya + abs(xa - xb) / 2);
			yb = min(w, yb + abs(xa - xb) / 2 - 1);
			if (ya - yb <= 1) cout << "BOB\n";
			else cout << "DRAW\n";
		}
	} else {
		if (ya > yb) {
			ya = max(1, ya - abs(xa - xb) / 2);
			yb = max(1, yb - abs(xa - xb) / 2);
			if (ya - yb <= 1) cout << "alice\n";
			else cout << "DRAW\n";
		} else {
			ya = min(w, ya + abs(xa - xb) / 2);
			yb = min(w, yb + abs(xa - xb) / 2);
			if (yb - ya <= 1) cout << "alice\n";
			else cout << "DRAW\n";
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}