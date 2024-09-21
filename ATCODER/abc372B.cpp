#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int M;
vector<int> ans;

void solve() {
	cin >> M;
	vector<int> v;
	for (int i = 1; i <= 1e5; i *= 3) v.push_back(i);
	for (int i = (int) v.size() - 1; i >= 0; --i) {
		while (M >= v[i]) {
			ans.push_back(i);
			M -= v[i];
		}
	}
	cout << ans.size() << '\n';
	for (auto i: ans) cout << i << ' ';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}