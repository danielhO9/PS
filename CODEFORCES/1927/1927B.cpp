#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
	vector<char> arr[n + 1];
	for (int i = 'a'; i <= 'z'; ++i) arr[0].push_back(char(i));
	for (int i = 0; i < n; ++i) {
		char c = arr[a[i]].back(); 
		cout << c;
		arr[a[i] + 1].push_back(c);
		arr[a[i]].pop_back();
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}