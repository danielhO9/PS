#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
int p[200001];

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> p[i];
	for (int i = 1; i <= n; ++i) if (i != p[i]) {
		if (i != n && p[i] == i + 1 && p[i + 1] == i) swap(p[i], p[i + 1]);
		else {
			cout << "NO\n";
			return;
		}
	}
	cout << "YES\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}