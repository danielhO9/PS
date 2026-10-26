#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	vector<int> arr; map<int, int> M;
	for (int i = 0; i < n; ++i) {
		int a; cin >> a;
		if (M[a] == 0) {
			arr.push_back(a);
			M[a] = 1;
		}
	}
	sort(arr.begin(), arr.end());
	int l = 0, m = arr.size(), r;
	for (int i = 0; i < m; ++i) {
		if (arr[i] <= arr[0] + n - 1) r = i;
		else break;
	}
	int ans = r - l + 1;
	for (int l = 0; l < m; ++l) {
		while (r != m - 1 && arr[r + 1] - arr[l] <= n - 1) ++r;
		ans = max(ans, r - l + 1);
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}