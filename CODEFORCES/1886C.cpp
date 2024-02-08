#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	string s; cin >> s; LL n = s.size();
	LL pos; cin >> pos; --pos;
	LL cnt = 0;
	for (LL i = n; i >= 1; --i) {
		if (pos >= i) {
			pos -= i;
			++cnt;
		}
		else break;
	}
	deque<char> l, r;
	for (auto i: s) r.push_back(i);
	while (true) {
		if (r.empty() || cnt == 0) break;
		if (!l.empty() && l.back() > r.front()) {
			l.pop_back(); --cnt;
		} else {
			l.push_back(r.front());
			r.pop_front();
		}
	}
	while (!r.empty()) {
		l.push_back(r.front());
		r.pop_front();
	}
	cout << l[pos];
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}