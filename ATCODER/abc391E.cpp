#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
string A;

pair<int, int> query(int l, int r) {
	// cout << l << ' ' << r << "\n";
	if (l + 1 == r) return {A[l] - '0', 1};
	int len = r - l;
	int t1 = l + len / 3;
	int t2 = t1 + len / 3;
	pair<int, int> ret[3] = {query(l, t1), query(t1, t2), query(t2, r)};
	int val = 0, sm = 0;
	for (int i = 0; i < 3; ++i) sm += ret[i].second;
	for (int i = 0; i < 3; ++i) val += ret[i].first;
	if (val == 3 || val == 0) {
		int mx = INT32_MIN;
		for (int i = 0; i < 3; ++i) mx = max(mx, ret[i].second);
		return {val / 3, sm - mx};
	} else {
		int res = (val == 2 ? 1 : 0);
		int mn = INT32_MAX;
		for (int i = 0; i < 3; ++i) if (ret[i].first == res) mn = min(mn, ret[i].second);
		return {res, mn};
	}
}

void solve() {
	cin >> N;
	cin >> A;
	int r = 1;
	for (int i = 0; i < N; ++i) r *= 3;
	auto ans = query(0, r);
	cout << ans.second;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}