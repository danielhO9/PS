#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	int n; cin >> n;
	deque<int> s;
	for (int i = 0; i < n; ++i) {
		char c; cin >> c;
		s.push_back(c - '0');
	}
	if (((int)s.size()) % 2 == 1) {
		cout << -1 << '\n';
		return;
	}
	vector<int> ans;
	int start = 0, end = n, p = 0;
	while (!s.empty()) {
		if (p > 300) {
			cout << -1 << '\n';
			return;
		}
		if (s.front() != s.back()) {
			s.pop_front(); s.pop_back();
			++start; --end;
		} else if (s.front() == 1) {
			++p;
			ans.push_back(start);
			end += 2;
			s.push_front(1); s.push_front(0);
		} else {
			++p;
			ans.push_back(end);
			end += 2;
			s.push_back(0); s.push_back(1);
		}
		if (s.empty()) {
			cout << p << '\n';
			for (auto i: ans) cout << i << ' ';
			cout << '\n';
			return;
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}

/*
1
6
001110
*/