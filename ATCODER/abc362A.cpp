#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int r, g, b; cin >> r >> g >> b;
	string s; cin >> s;
	if (s == "Red") {
		cout << min(g, b);
	}
	if (s == "Blue") {
		cout << min(g, r);
	}
	if (s == "Green") {
		cout << min(r, b);
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}