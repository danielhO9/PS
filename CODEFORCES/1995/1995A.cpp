#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int n, k; cin >> n >> k;
	vector<int> v;
	for (int i = 1; i < n; ++i) {
		v.push_back(i);
		v.push_back(i);
	}
	v.push_back(n);
	sort(v.begin(), v.end());
	int sum = 0, cnt = 0;
	while (sum < k) {
		sum += v.back(); v.pop_back();
		++cnt;
	}
	cout << cnt << "\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}