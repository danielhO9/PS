#include <bits/stdc++.h>
using namespace std;

void solve() {
	int Q; cin >> Q;
	stack<int> s;
	for (int i = 0; i < 100; ++i) s.push(0);
	while (Q--) {
		int t; cin >> t;
		if (t == 1) {
			int x; cin >> x;
			s.push(x);
		} else {
			cout << s.top() << '\n'; s.pop();
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}