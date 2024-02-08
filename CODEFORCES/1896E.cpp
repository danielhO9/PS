#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL sum(vector<LL> &tree, int i) {
    LL ans = 0;
    while (i > 0) {
        ans += tree[i];
        i -= (i & -i);
    }
    return ans;
}

void update(vector<LL> &tree, int i, LL diff) {
    while (i < tree.size()) {
        tree[i] += diff;
        i += (i & -i);
    }
}

void solve() {
	int n; cin >> n;
	int a[n + 1]; for (int i = 1; i <= n; ++i) cin >> a[i];
	vector<LL> tree(2 * n + 1, 0);
	vector<pair<int, int>> V;
	for (int i = 1; i <= n; ++i) {
		if (i <= a[i]) {
			V.push_back({i, a[i]});
			V.push_back({i + n, a[i] + n});
		} else {
			V.push_back({i, a[i] + n});
		}
	}
	int ans[n + 1];
	sort(V.begin(), V.end(), greater<pair<int, int>>());
	for (auto [l, r]: V) {
		if (l <= n) ans[a[l]] = r - l - sum(tree, r) + sum(tree, l - 1);
		update(tree, r, 1); 
	}
	for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}