#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int n; cin >> n;
	deque<int> a(n); for (int i = 0; i < n; ++i) cin >>a[i];
	sort(a.begin(), a.end());
	int t = 0;
	while (a.size() > 1) {
		if (t == 0) a.pop_front();
		else a.pop_back();
		t ^= 1;
	}
	cout << a[0] << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}