#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
int arr[2][200000];

void solve() {
	cin >> n;
	string s; cin >> s;
	for (int i = 0; i < n; ++i) {
		arr[0][i] = (s[i] == 'x');
	}
	cin >> s;
	for (int i = 0; i < n; ++i) {
		arr[1][i] = (s[i] == 'x');
	}
	int ans = 0;
	for (int i = 0; i < n - 2; ++i) {
		if (arr[0][i] && !arr[0][i + 1] && arr[0][i + 2] && !arr[1][i] && !arr[1][i + 2]) ++ans;
		if (arr[1][i] && !arr[1][i + 1] && arr[1][i + 2] && !arr[0][i] && !arr[0][i + 2]) ++ans;
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}