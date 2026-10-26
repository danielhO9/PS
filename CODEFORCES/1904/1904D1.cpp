#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void init(vector<LL> &a, vector<LL> & tree, int node, int start, int end) {
	if (start == end) tree[node] = a[start];
	else {
		init(a, tree, node * 2, start, (start + end) / 2);
		init(a, tree, node * 2 + 1, (start + end) / 2 + 1, end);
		tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
	}
}

LL query(vector<LL> &tree, int node, int start, int end, int left, int right) {
	if (left > end || right < start) return 987654321;
	if (left <= start && end <= right) return tree[node];
	LL lsum = query(tree, node * 2, start, (start + end) / 2, left, right);
	LL rsum = query(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
	return min(lsum, rsum);
}

void solve() {
	LL n; cin >> n;
	vector<LL> a(n), b(n);
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < n; ++i) cin >> b[i];
	vector<LL> l(n, -1);
	vector<LL> r(n, -1);
	deque<pair<LL, LL>> Q;
	for (LL i = 0; i < n; ++i) {
		while (!Q.empty() && Q.front().first <= a[i]) Q.pop_front();
		Q.push_front({a[i], i});
		LL start = 0, end = Q.size(), mid;
		while (start < end) {
			mid = (start + end) / 2;
			if (Q[mid].first == b[i]) {
				l[i] = Q[mid].second;
				break;
			} else if (Q[mid].first > b[i]) {
				end = mid;
			} else {
				start = mid + 1;
			}
		}
	}
	Q.clear();
	for (LL i = n - 1; i >= 0; --i) {
		while (!Q.empty() && Q.front().first <= a[i]) Q.pop_front();
		Q.push_front({a[i], i});
		LL start = 0, end = Q.size(), mid;
		while (start < end) {
			mid = (start + end) / 2;
			if (Q[mid].first == b[i]) {
				r[i] = Q[mid].second;
				break;
			} else if (Q[mid].first > b[i]) {
				end = mid;
			} else {
				start = mid + 1;
			}
		}
	}
	// for (auto i: l) cout << i << ' ';
	// cout << '\n';
	// for (auto i: r) cout << i << ' ';


	int h = (int)ceil(log2(n));
	int tree_size = (1 << (h + 1));
	vector<LL> tree(tree_size);
	init(b, tree, 1, 0, n - 1);
	for (int i = 0; i < n; ++i) {
		if (l[i] != -1) {
			LL minb = query(tree, 1, 0, n - 1, l[i], i);
			if (minb >= b[i]) continue;
		}
		if (r[i] == -1) {
			cout << "NO\n"; return;
		}
		LL minb = query(tree, 1, 0, n - 1, i, r[i]);
		if (minb < b[i]) {
			cout << "NO\n"; return;
		}
	}
	cout << "YES\n"; return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}