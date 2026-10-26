#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, k;
int a[100];

void solve() {
	cin >> n >> k;
	vector<int> mod[100];
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < n; ++i) {
		mod[a[i] % k].push_back(i);
	}
	for (int i = 0; i < k; ++i) {
		if (mod[i].size() == 1) {
			cout << "YES\n";
			cout << mod[i][0] + 1 << '\n';
			return;
		}
	}
	cout << "NO\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}