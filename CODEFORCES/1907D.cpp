#include <bits/stdc++.h>
using namespace std;

int n, l[200000], r[200000];

bool check(int x) {
	int low = 0, high = 0;
	for (int i = 0; i < n; ++i) {
		low -= x; high += x;
		if (high < l[i] || r[i] < low) return false;
		if (low < l[i]) low = l[i];
		if (high > r[i]) high = r[i];
	}
	return true;
}

int solution() {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> l[i] >> r[i];
	int m = 0, M = 1e9, mid;
	while (1) {
		mid = (m + M) / 2;
		bool possible = check(mid);
		if (possible) M = mid;
		else m = mid + 1;
		if (m == M) break;
	}
	return M;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	for (int i = 0; i < t; ++i) cout << solution() << '\n';
}