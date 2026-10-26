#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int n; cin >> n;
	vector<int> s(n); for (int i = 0; i < n; ++i) cin >> s[i];
	if (s[0] != 0) {
		cout << 0 << endl;
		int temp; cin >> temp;
		return;
	}
	int num = 0;
	while (num < n && s[num] == num) ++num;
	cout << num << endl;
	while (true) {
		int temp; cin >> temp;
		if (temp < 0) return;
		cout << temp << endl;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}