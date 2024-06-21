#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int n; cin >> n;
	vector<int> arr[4];
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < 4; ++j) {
			int num; cin >> num;
			arr[j].push_back(num);
		}
	}
	unordered_map<int, int> M;
	ll ans = 0;
	for (auto i: arr[0]) for (auto j: arr[1]) ++M[i + j];
	for (auto i: arr[2]) for (auto j: arr[3]) if (M.find(-(i + j)) != M.end()) ans += M[-(i + j)];
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}