#include <bits/stdc++.h>
using namespace std;

void update(vector<pair<int, int>>& tree, vector<pair<int, int>>& lazy, int node, int minv, int maxv, int type) {
	if (type == 0) {
		tree[node].first = max(tree[node].first, minv);
		tree[node].second = max(tree[node].second, minv);
		tree[node].first = min(tree[node].first, maxv);
		tree[node].second = min(tree[node].second, maxv);
	} else {
		lazy[node].first = max(lazy[node].first, minv);
		lazy[node].second = max(lazy[node].second, minv);
		lazy[node].first = min(lazy[node].first, maxv);
		lazy[node].second = min(lazy[node].second, maxv);
	}
}

void update_lazy(vector<pair<int, int>>& tree, vector<pair<int, int>>& lazy, int node, int start, int end) {
    if (!(lazy[node].first == INT32_MIN && lazy[node].second == INT32_MAX)) {
		// cout << "lazy 들어옴\n";
		// cout << lazy[node].first << ' ' << lazy[node].second << '\n';
		// cout << tree[node].first << ' ' << tree[node].second << '\n';
        update(tree, lazy, node, lazy[node].first, lazy[node].second, 0);
        if (start != end) {
			update(tree, lazy, node * 2, lazy[node].first, lazy[node].second, 1);
			update(tree, lazy, node * 2 + 1, lazy[node].first, lazy[node].second, 1);
        }
        lazy[node] = {INT32_MIN, INT32_MAX};
		// cout << "lazy 나가요\n";
		// cout << lazy[node].first << ' ' << lazy[node].second << '\n';
		// cout << tree[node].first << ' ' << tree[node].second << '\n';
    }
}

void update_range(vector<pair<int, int>>& tree, vector<pair<int, int>>& lazy, int node, int start, int end, int left, int right, int h, int t) {
    update_lazy(tree, lazy, node, start, end);
    if (left > end || right < start) {
        return;
    }
    if (left <= start && end <= right) {
        if (t == 1) update(tree, lazy, node, h, INT32_MAX, 0); 
		else update(tree, lazy, node, INT32_MIN, h, 0);
        if (start != end) {
            if (t == 1) {
				update(tree, lazy, node * 2, h, INT32_MAX, 1);
				update(tree, lazy, node * 2 + 1, h, INT32_MAX, 1); 
			}
			else {
				update(tree, lazy, node * 2, INT32_MIN, h, 1);
				update(tree, lazy, node * 2 + 1, INT32_MIN, h, 1);
			}
        }
        return;
    }
    update_range(tree, lazy, node * 2, start, (start + end) / 2, left, right, h, t);
    update_range(tree, lazy, node * 2 + 1, (start + end) / 2 + 1, end, left, right, h, t);
	tree[node] = tree[node * 2];
	tree[node].first = min(tree[node].first, tree[node * 2 + 1].first);
	tree[node].second = max(tree[node].second, tree[node * 2 + 1].second);
}

pair<int, int> query(vector<pair<int, int>>& tree, vector<pair<int, int>>& lazy, int node, int start, int end, int left, int right) {
    update_lazy(tree, lazy, node, start, end);
    if (left > end || right < start) {
        return {INT32_MAX, INT32_MAX};
    }
    if (left <= start && end <= right) {
        return tree[node];
    }
    pair<int, int> lsum = query(tree, lazy, node * 2, start, (start+end) / 2, left, right);
    pair<int, int> rsum = query(tree, lazy, node * 2 + 1, (start+end) / 2 + 1, end, left, right);
    if (lsum.first != INT32_MAX) return lsum;
	return rsum;
}

void solve() {
	int n, k; cin >> n >> k;
	// 0 ~ MAX_N - 1
	int MAX_N = n;
    int h = (int)ceil(log2(MAX_N));
    int tree_size = (1 << (h + 1));
    vector<pair<int, int>> tree(tree_size);
    vector<pair<int, int>> lazy(tree_size);
	for (auto& i: tree) i = {0, 0};
	for (auto& i: lazy) i = {INT32_MIN, INT32_MAX};
	while (k--) {
		int what, left, right, h; cin >> what >> left >> right >> h;
		update_range(tree, lazy, 1, 0, MAX_N - 1, left, right, h, what);
		// cout << "tree\n";
		// for (auto i: tree) cout << i.first << ' ' << i.second << '\n';
		// cout << "lazy\n";
		// for (auto i: lazy) cout << i.first << ' ' << i.second << '\n';
		// cout << "lazy\n";
		// for (auto i: lazy) cout << i.first << ' ' << i.second << '\n';
	}
	for (int i = 0; i < n; ++i) cout << query(tree, lazy, 1, 0, MAX_N - 1, i, i).first << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}