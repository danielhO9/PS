#include <bits/stdc++.h>
using namespace std;

void solve() {
	int cur = 3;
	string s; cin >> s;
	deque<int> dq;
	for (auto i: s) dq.push_back(i - '0');
	int cnt = 0;
	vector<int> last;
	while (dq.size() >= 3) {
		int f = dq[0], s = dq[1], t = dq[2];
		if ((f + s + t) % 3 == 0) {
			dq.pop_front();
			dq.pop_front();
			dq.push_front(f);
			if (!last.empty()) {
				dq.push_front(last.back());
				last.pop_back();
			}
			++cnt;
		} else {
			last.push_back(dq.front());
			dq.pop_front();
		}
	}
	if (cnt % 2) cout << "Anda\n";
	else cout << "Kamu\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}