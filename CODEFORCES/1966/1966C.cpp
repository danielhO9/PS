#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
ll a[200000];

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	set<ll> s;
	for (int i = 0; i < n; ++i) s.insert(a[i]);
	vector<ll> v;
	v.push_back(0);
	for (auto i: s) v.push_back(i);
	int t = 0;
	for (int i = 1; i < v.size(); ++i) {
		if (v[i] - v[i - 1] >= 2) {
			if (t) {
				cout << "Bob\n";
				return;
			}
			else {
				cout << "Alice\n";
				return;
			}
		}
		t ^= 1;
	}
	if (t == 0) {
		cout << "Bob\n";
		return;
	}
	else {
		cout << "Alice\n";
		return;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}