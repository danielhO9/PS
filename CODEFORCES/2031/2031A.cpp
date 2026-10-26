#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
int h[50];

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> h[i];
	vector<int> cnt(51);
	for (int i = 0; i < n; ++i) ++cnt[h[i]];
	int mx = *max_element(cnt.begin(), cnt.end());
	cout << n - mx << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}