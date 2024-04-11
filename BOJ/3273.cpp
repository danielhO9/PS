#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int n; cin >> n;
	int a[n]; for (int i = 0; i < n; ++i) cin >> a[i];
	int x; cin >> x;
	sort(a, a + n);
	int l = 0, r = n - 1;
	int ans = 0;
	while (l < r) {
		if (a[l] + a[r] < x) ++l;
		else if (a[l] + a[r] == x) {
			++ans;
			++l; --r;
		} else --r;
	}
	cout << ans;
}