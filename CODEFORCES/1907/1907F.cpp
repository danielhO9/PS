#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
 
int n, a[200000], m[200000], p[200000];
 
int solution() {
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		a[i + n] = a[i];
	}
	m[0] = 0; p[0] = 0;
	for (int i = 1; i < 2 * n; ++i) {
		if (a[i - 1] >= a[i]) m[i] = m[i - 1] + 1;
		else m[i] = 0;
		if (a[i - 1] <= a[i]) p[i] = p[i - 1] + 1;
		else p[i] = 0;
	}
	int ret = 1000000;
	for (int i = n - 1; i < 2 * n; ++i) {
		if (p[i] == n - 1) {
			if (i == n - 1) return 0;
			ret = min({ret, i - n + 3, 2 * n - i - 1});
		}
		if (m[i] == n - 1) {
			if (i == n - 1) return 1;
			ret = min({ret, i - n + 2, 2 * n - i});
		}
	}
	if (ret != 1000000) return ret;
	return -1;
}
 
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	for (int i = 0; i < t; ++i) cout << solution() << '\n';
}