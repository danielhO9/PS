#include <bits/stdc++.h>
using namespace std;

int n;

void solve() {
	cin >> n;
	vector<pair<int, int>> v;
	int s[100001]; memset(s, 0, sizeof(s));
	int e[100001]; memset(e, 0, sizeof(e));
	int sum[100001]; memset(sum, 0, sizeof(sum));

	for (int i = 0; i < n; ++i) {
		int a, b; cin >> a >> b;
		v.push_back({a, b});
		++s[a]; ++e[b];
		++sum[a];
		if (b < 100001) --sum[b];
	}
	for (int i = 1; i <= 100000; ++i) {
		s[i] += s[i - 1];
		e[i] += e[i - 1];
	}
	int ans1 = 0;
	for (auto [a, b]: v) {
		ans1 = max(ans1, n - (e[a] + s[100000] - s[b - 1]));
	}
	int ans2 = 0, now = 0;
	for (int i = 1; i <= 100000; ++i) {
		now += sum[i];
		ans2 = max(ans2, now);
	}
	cout << ans1 << ' ' << ans2;

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}