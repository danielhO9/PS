#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
int a[100];
bool b[10000];

void init() {
	for (int i = 1; i <= 100; i += 2) b[i * i] = true;
}

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	int ans = 0;
	int sum = 0;
	for (int i = 0; i < n; ++i) {
		sum += a[i];
		if (b[sum]) ++ans;
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	init();
	int t; cin >> t;
	while (t--) solve();
}