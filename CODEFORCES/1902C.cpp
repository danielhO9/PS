#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL n, a[200000];

LL gcd2(LL a, LL b) { 
	if (a < b) return gcd2(b, a);
	if (a % b == 0) return b;
	else return gcd2(b, a % b);
}

LL solution() {
	cin >> n;
	LL maxa = -(1e9);
	LL mina = 1e9;
	LL ans = 0;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		maxa = max(maxa, a[i]);
		mina = min(mina, a[i]);
	}
	if (n == 1) return 1;
	LL x = maxa - mina;
	for (int i = 0; i < n; ++i) {
		if (maxa != a[i]) x = gcd2(x, maxa - a[i]);
	}
	int v[n];
	memset(v, 0, sizeof(v));
	for (int i = 0; i < n; ++i) {
		ans += (maxa - a[i]) / x;
		if ((maxa - a[i]) / x < n) v[(maxa - a[i]) / x] = 1;
	}
	for (int i = 0; i < n; ++i) {
		if (v[i] == 0) return ans + i;
	}
	return ans + n;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) cout << solution() << '\n';
}