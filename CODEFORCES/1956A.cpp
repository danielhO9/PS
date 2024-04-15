#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int k, q; cin >> k >> q;
	vector<int> a(k); for (int i = 0; i < k; ++i) cin >> a[i];
	int mina = a[0] - 1;
	vector<int> n(q); for (int i = 0; i < q; ++i) cin >> n[i];
	for (int i = 0; i < q; ++i) {
		cout << min(mina, n[i]) << ' ';
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}