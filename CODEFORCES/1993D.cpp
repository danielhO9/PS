#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, k;
int rem;
int a[500000];
vector<int> v;

int check(int val) {
	if (n % k) {
		vector<int> tmp(n, 0);
		for (int i = 0; i < n; ++i) if (a[i] < val) tmp[i] = 1;
		vector<int> cache(n, -1);
		cache[0] = tmp[0];
		for (int i = 1; i < k; ++i) {
			cache[i] = tmp[i] + cache[i - 1];
		}
		cache[k - 1] = 0;
		for (int i = k; i < n; ++i) {
			cache[i] = min(tmp[i] + cache[i - 1], cache[i - k]);
		}
		return cache[n - 1];
	} else {
		vector<int> tmp(n, 0);
		for (int i = 0; i < n; ++i) if (a[i] < val) tmp[i] = 1;
		vector<int> cache(n, 987654321);
		cache[0] = tmp[0];
		for (int i = 1; i < k; ++i) cache[i] = tmp[i] + cache[i - 1];
		for (int i = k; i < n; ++i) {
			if (i % k == 0) cache[i] = tmp[i];
			cache[i] = min(cache[i], min({tmp[i] + cache[i - 1], cache[i - k]}));
		}
		// 5 9 2 6 5 4 6
		// 1 0 1 0 1 1 0
		// cout << val << ' ' << cache[n - 1] << '\n';
		return cache[n - 1];
	}
	
}

void solve() {
	cin >> n >> k;
	rem = n % k;
	if (rem == 0) rem = k;
	rem = (rem - 1) / 2;
	for (int i = 0; i < n; ++i) cin >> a[i];
	if (n <= k) {
		sort(a, a + n);
		cout << a[(n - 1) / 2] << '\n';
		return;
	}
	set<int> s;
	for (int i = 0; i < n; ++i) s.insert(a[i]);
	v.clear();
	for (auto i: s) v.push_back(i);
	
	int l = 0, r = v.size();
	while (l + 1 < r) {
		int mid = (l + r) / 2;
		if (check(v[mid]) <= rem) l = mid;
		else r = mid;
	}
	cout << v[l] << "\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}