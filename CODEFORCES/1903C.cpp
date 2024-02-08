#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int n, a[100000];
LL s[100000];

void solution() {
	LL ans = 0;
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = n - 1; i >= 0; --i) {
		if (i == n - 1) s[i] = a[i];
		else s[i] = a[i] + s[i + 1];
		if (i == 0 || s[i] > 0) ans += s[i];
	}
	cout << ans << '\n';
	return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	for (int i = 0; i < t; ++i) solution();
}