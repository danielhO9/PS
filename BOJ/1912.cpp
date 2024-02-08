#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int n; cin >> n;
	int a[n]; for (int i = 0; i < n; ++i) cin >> a[i];
	int cache[n];
	cache[0] = a[0];
	for (int i = 1; i < n; ++i) {
		cache[i] = max(0, cache[i - 1]) + a[i];
	}
	cout << *max_element(cache, cache + n);
}