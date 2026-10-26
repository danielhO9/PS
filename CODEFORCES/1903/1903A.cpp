#include <bits/stdc++.h>
using namespace std;

int n, a[100], k;

void solution() {
	cin >> n >> k;
	for (int i = 0; i < n; ++i) cin >> a[i];
	if (k != 1) {
		cout << "YES" << '\n';
		return;
	} else {
		for (int i = 1; i < n; ++i) if (a[i] < a[i - 1]) {
			cout << "NO" << '\n';
			return;
		}
		cout << "YES" << '\n';
		return;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	for (int i = 0; i < t; ++i) solution();
}