#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
	deque<int> Q[2]; Q[0].push_back(0); Q[1].push_back(0);
	int ans = 0;
	for (int i = n - 1; i >= 0; --i) {
		if (Q[0].front() > a[i] && Q[1].front() <= a[i]) Q[1].push_front(a[i]);
		else if (Q[0].front() <= a[i] && Q[1].front() > a[i]) Q[0].push_front(a[i]);
		else if (Q[0].front() <= a[i] && Q[1].front() <= a[i]) {
			if (Q[0].front() < Q[1].front()) Q[1].push_front(a[i]);
			else Q[0].push_front(a[i]);
		} else {
			if (Q[0].front() < Q[1].front()) Q[1].push_front(a[i]);
			else Q[0].push_front(a[i]);
			++ans;
		}
	}
	cout << ans << '\n';

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}