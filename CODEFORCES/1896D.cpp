#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n, q; cin >> n >> q;
	set<int> S;
	int a[n]; for (int i = 0; i < n; ++i) {
		cin >> a[i];
		if (a[i] == 1) S.insert(i);
	}
	while (q--) {
		int op; cin >> op;
		if (op == 1) {
			int s; cin >> s;
			if ((2 * n - (int) S.size()) % 2 == s % 2) {
				if (2 * n - (int) S.size() >= s) cout << "YES" << '\n';
				else cout << "NO" << '\n';
			} else {
				if (S.empty()) cout << "NO" << '\n';
				else {
					int s1 = 2 * (*S.rbegin()) - ((int) S.size() - 1);
					int s2 = 2 * (n - 1 - *S.begin()) - ((int) S.size() - 1);
					if (s <= max(s1, s2)) cout << "YES" << '\n';
					else cout << "NO" << '\n';
				}
			}
		} else {
			int i, v; cin >> i >> v; --i;
			S.erase(i);
			if (v == 1) S.insert(i);
		}
	}
}

/*
2
5 5
2 1 2 1 2
1 5
1 6
1 7
2 4 2
1 7
3 2
2 2 2
1 6
1 5
*/

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}