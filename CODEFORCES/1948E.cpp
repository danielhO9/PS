#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n, k; cin >> n >> k;
	vector<int> a(n + 1), c(n + 1);
	int q;
	int cnt = 0;
	q = n % k == 0 ? n / k : n / k + 1;
	for (int i = 0; i < q - 1; ++i) {
		++cnt;
		int start = k * i + 1, end = k * i + k;
		int num = (start + end) / 2, ind = start;
		while (num <= end) {
			a[ind] = num;
			c[ind] = cnt;
			++ind; ++num;
		}
		num = start;
		while (num < (start + end) / 2) {
			a[ind] = num;
			c[ind] = cnt;
			++ind; ++num;
		}
	}
	int start = k * (q - 1) + 1, end = n;
	++cnt;
	int num = (start + end) / 2, ind = start;
	while (num <= end) {
		a[ind] = num;
		c[ind] = cnt;
		++ind; ++num;
	}
	num = start;
	while (num < (start + end) / 2) {
		a[ind] = num;
		c[ind] = cnt;
		++ind; ++num;
	}

	for (int i = 1; i <= n; ++i) cout << a[i] << ' ';
	cout << '\n';
	cout << q << '\n';
	for (int i = 1; i <= n; ++i) cout << c[i] << ' ';
	cout << '\n';

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}