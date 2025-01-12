#include <bits/stdc++.h>
using namespace std;

string ss;

void solve() {
	cin >> ss;
	deque<char> s;
	for (auto i: ss) s.push_back(i);
	while (true) {
		int fcnt = 0, bcnt = 0;
		char f = s.front(), b = s.back();
		if (f != b) {
			cout << 0;
			break;
		}
		while (s.size() > 0 && s.front() == f) {
			s.pop_front();
			++fcnt;
		}
		while (s.size() > 0 && s.back() == b) {
			s.pop_back();
			++bcnt;
		}
		// cout << fcnt << ' ' << bcnt << '\n';
		if (s.size() == 0) {
			if (fcnt + bcnt + 1 >= 3) cout << fcnt + bcnt + 1;
			else cout << 0;
			return;
		}

		if (fcnt + bcnt < 3) {
			cout << 0;
			return;
		}

	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}