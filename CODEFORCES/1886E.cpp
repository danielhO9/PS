#include <bits/stdc++.h>
using namespace std;
int n, m;

int matchCache(int x, vector<int>& cache, vector<vector<int>>& mn, vector<pair<int, int>>& choice) {
	if (x == 0) return 0;
	int& ret = cache[x];
	if (ret != -1) return ret;
	ret = n + 1;
	for (int i = 0; i < m; ++i) if ((x | (1 << i)) == x) {
		int index = matchCache(x ^ (1 << i), cache, mn, choice);
		if (index != n + 1 && ret > mn[i][index]) {
			ret = mn[i][index];
			choice[x] = {i, index};
		}
	}
	return ret;
}

void reconstruct(vector<vector<int>>& ans, vector<pair<int, int>>& choice, vector<vector<int>>& mn, int x, int l) {
	if (x == 0) return;
	for (int i = l; i < mn[choice[x].first][l]; ++i) if (i != n) ans[choice[x].first].push_back(i);
	reconstruct(ans, choice, mn, x ^ (1 << choice[x].first), choice[x ^ (1 << choice[x].first)].second);
}

void solve() {
	cin >> n >> m;
	vector<int> a(n), b(m), ord(n);
	for (int i = 0; i < n; ++i) ord[i] = i;
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < m; ++i) cin >> b[i];
	sort(ord.begin(), ord.end(), [&a](int i, int j) { return a[i] > a[j]; });
	vector<vector<int>> mn(m, vector<int>(n));
	for (int i = 0; i < m; ++i) {
		int r = 0;
		for (int l = 0; l < n; ++l) {
			r = max(r, l + 1);
			while (r <= n && a[ord[r - 1]] * (r - l) < b[i]) ++r;
			mn[i][l] = r;
		}
	}
	vector<int> cache(1 << m, -1);
	vector<pair<int, int>> choice(1 << m);
	if (matchCache((1 << m) - 1, cache, mn, choice) == n + 1) {
		cout << "NO" << '\n';
		return;
	}
	cout << "YES" << '\n';
	vector<vector<int>> ans(m);
	reconstruct(ans, choice, mn, (1 << m) - 1, choice[(1 << m) - 1].second);
	for (auto i: ans) {
		cout << i.size() << ' ';
		for (auto j: i) cout << ord[j] + 1 << ' ';
		cout << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}