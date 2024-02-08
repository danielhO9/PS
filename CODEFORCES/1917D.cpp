#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL MOD = 998244353;

void update(vector<LL> &a, vector<LL>& tree, int node, int start, int end, int index, LL val) {
	if (index < start || index > end) return;
	if (start == end) {
		a[index] = val;
		tree[node] = val;
		return;
	}
	update(a, tree, node * 2, start, (start + end) / 2, index, val);
	update(a, tree, node * 2 + 1, (start + end) / 2 + 1, end, index, val);
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

LL query(vector<LL> &tree, int node, int start, int end, int left, int right) {
	if (left > end || right < start) return 0;
	if (left <= start && end <= right) return tree[node];
	LL lsum = query(tree, node * 2, start, (start + end) / 2, left, right);
	LL rsum = query(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
	return lsum + rsum;
}

void solve() {
	LL n, k; cin >> n >> k;
	vector<LL> p(n); for (int i = 0; i < n; ++i) {
		cin >> p[i]; ++p[i];
		p[i] /= 2LL;
	}
	vector<LL> q(k); for (int i = 0; i < k; ++i) cin >> q[i];
	int h = (int)ceil(log2(k));
	int tree_size = (1 << (h + 1));
	vector<LL> ptree(tree_size);
	vector<LL> parr(k);
	LL cnt = 0;
	for (int i = 0; i < k; ++i) {
		cnt += query(ptree, 1, 0, k - 1, q[i], k - 1);
		cnt %= MOD;
		update(parr, ptree, 1, 0, k - 1, q[i], 1);
	}
	LL ans = cnt * n; ans %= MOD;
	h = (int)ceil(log2(n + 1));
	tree_size = (1 << (h + 1));
	vector<LL> tree(tree_size);
	vector<LL> arr(n + 1);
	for (LL i = 0; i < n; ++i) {
		ans += query(tree, 1, 0, n, p[i], n) * k; ans %= MOD;
		LL tq = 2, tk = 1;
		while (true) {
			LL temp = p[i] * 2 - 1; temp *= tq;
			temp += 2; temp /= 2LL;
			if (temp > n || tk == k) break;
			ans += query(tree, 1, 0, n, temp, n) * (k - tk); ans %= MOD;
			tq *= 2LL; ++tk;
		}
		tq = 2, tk = 1; bool one = false;
		while (true) {
			if (tk == k) break;
			if (one) {
				LL temp = (k - tk + 1) * (k - tk) / 2LL; temp %= MOD;
				ans += query(tree, 1, 0, n, 0, n) * temp; ans %= MOD;
				break;
			} else {
				LL temp = p[i] * 2 - 1;
				temp += tq - 1; temp /= tq;
				temp += 2; temp /= 2LL;
				ans += query(tree, 1, 0, n, temp, n) * (k - tk); ans %= MOD;
				tq *= 2LL;
				if (temp == 1LL) one = true;
			}
			++tk;
		}
		update(arr, tree, 1, 0, n, p[i], 1);
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}