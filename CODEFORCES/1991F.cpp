#include <bits/stdc++.h>
using namespace std;

int n, q;
int a[100000];

bool tri(int l, int r) {
	if (r  - l + 1 >= 48) return true;
	vector<int> v;
	for (int i = l - 1; i < r; ++i) v.push_back(a[i]);
	sort(v.begin(), v.end());
	vector<pair<int, int>> arr[v.size()];
	for (int i = 0; i < (int) v.size() - 2; ++i) {
		for (int j = i + 1; j < (int) v.size() - 1; ++j) {
			for (int k = j + 1; k < v.size(); ++k) {
				if (v[i] + v[j] > v[k]) arr[i].push_back({j, k});
				else break;
			}
		}
	}

	for (int i = 0; i < (int) v.size() - 1; ++i) {
		for (int j = i + 1; j < v.size(); ++j) {
			for (auto k: arr[i]) {
				for (auto l: arr[j]) {
					if (k.first != j && k.first != l.first && k.first != l.second && k.second != j && k.second != l.first && k.second != l.second) return true;
				}
			}
		}
	}
	return false;
}

void solve() {
	cin >> n >> q;
	for (int i = 0; i < n; ++i) cin >> a[i];
	while (q--) {
		int l, r; cin >> l >> r;
		if (tri(l, r)) cout << "YES\n";
		else cout << "NO\n";
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}