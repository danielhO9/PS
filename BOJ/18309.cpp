#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	string s;
	int mx = -51, mn = 51;
	while (cin >> s) {
		if (s.size() > 3) continue;
		int t = stoi(s);
		mx = max(mx, t);
		mn = min(mn, t);
	}
	cout << mn << ' ' << mx;
}