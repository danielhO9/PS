#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int n, q;
LL a[100000], k, b[100000], x[100000];

void solution() {
	LL ans = 0, nk;
	for (int i = 0; i < n; ++i) b[i] = a[i];
	for (LL i = 59; i >= 0; --i) {
		nk = k;
		bool possible = true;
		for (int j = 0; j < n; ++j) {
			x[j] = ((1LL << i) | b[j]);
			for (int l = 0; l < i; ++l) x[j] &= ~(1LL << l);
			x[j] = max(x[j], b[j]);
			if (x[j] - b[j] > nk) {
				possible = false;
				break;
			} else {
				nk -= x[j] - b[j];
			}
		}
		if (possible) {
			k = nk;
			for (int j = 0; j < n; ++j) b[j] = x[j];
			ans += (1LL << i);
		}
	}
	cout << ans << '\n';
	return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> q;
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < q; ++i) {
		cin >> k;
		solution();
	}
}