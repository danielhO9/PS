#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string s, t;

void solve() {
	cin >> s >> t;
	deque<pair<int, int>> sdq, tdq;
	int cur = -1;
	int cnt = 0;
	for (int i = 0; i < s.size(); ++i) {
		if (s[i] - '0' == cur) {
			++cnt;
		} else {
			if (cnt != 0) sdq.push_back({cur, cnt});
			cur = s[i] - '0';
			cnt = 1;
		}
	}
	if (cnt != 0) sdq.push_back({cur, cnt});

	cur = -1, cnt =0;
	for (int i = 0; i < t.size(); ++i) {
		if (t[i] - '0' == cur) {
			++cnt;
		} else {
			if (cnt != 0) tdq.push_back({cur, cnt});
			cur = t[i] - '0';
			cnt = 1;
		}
	}
	if (cnt != 0) tdq.push_back({cur, cnt});
	int ans = 0;
	while (true) {
		// for (auto i: sdq) {
		// 	for (int j = 0; j < i.second; ++j) cout << i.first;
		// }
		// cout << '\n';
		// for (auto i: tdq) {
		// 	for (int j = 0; j < i.second; ++j) cout << i.first;
		// }
		// cout << "\n\n";

		if (sdq.empty() && tdq.empty()) {
			cout << ans << '\n'; return;
		}
		if (sdq.empty() || tdq.empty()) {
			cout << -1 << '\n'; return;
		}
		auto sf = sdq.front(), tf = tdq.front();
		if (sf.first != tf.first) {
			sdq.pop_front();
			if (sdq.empty()) { cout << -1 << '\n'; return; }
			auto ss = sdq.front(); sdq.pop_front();
			if (!sdq.empty()) sdq.front().second += sf.second;
			else sdq.push_front(sf);
			sdq.push_front(ss);
			++ans;
		} else {
			if (sf.second == tf.second) {
				tdq.pop_front(); sdq.pop_front();
			} else if (sf.second > tf.second) {
				cout << -1 << '\n'; return;
			} else {
				sdq.pop_front();
				if (sdq.empty()) { cout << -1 << '\n'; return; }
				auto ss = sdq.front(); sdq.pop_front();
				if (sdq.empty()) { cout << -1 << '\n'; return; }
				auto st = sdq.front(); sdq.pop_front();
				++ans;
				if (!sdq.empty()) sdq.front().second += ss.second;
				else sdq.push_front(ss);
				sdq.push_front({sf.first, sf.second + st.second});
			}
		}
	}

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}