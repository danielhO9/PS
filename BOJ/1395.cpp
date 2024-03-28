#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void update_lazy(vector<ll>& tree, vector<ll>& lazy, int node, int start, int end) {
    if (lazy[node] == 1) {
        tree[node] = (end - start + 1) - tree[node];
        if (start != end) {
            lazy[node * 2] ^= 1;
            lazy[node * 2 + 1] ^= 1;
        }
        lazy[node] = 0;
    }
}

void update_range(vector<ll>& tree, vector<ll>& lazy, int node, int start, int end, int left, int right) {
    update_lazy(tree, lazy, node, start, end);
    if (left > end || right < start) {
        return;
    }
    if (left <= start && end <= right) {
        tree[node] = (end - start + 1) - tree[node];
        if (start != end) {
            lazy[node * 2] ^= 1;
            lazy[node * 2 + 1] ^= 1;
        }
        return;
    }
    update_range(tree, lazy, node * 2, start, (start + end) / 2, left, right);
    update_range(tree, lazy, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll query(vector<ll>& tree, vector<ll>& lazy, int node, int start, int end, int left, int right) {
    update_lazy(tree, lazy, node, start, end);
    if (left > end || right < start) {
        return 0;
    }
    if (left <= start && end <= right) {
        return tree[node];
    }
    ll lsum = query(tree, lazy, node * 2, start, (start+end) / 2, left, right);
    ll rsum = query(tree, lazy, node * 2 + 1, (start+end) / 2 + 1, end, left, right);
    return lsum + rsum;
}

void solve() {
	int N, M; cin >> N >> M;
	// 0 ~ MAX_N - 1
	int MAX_N = N + 1;
    vector<ll> a(MAX_N);
    int h = (int)ceil(log2(MAX_N));
    int tree_size = (1 << (h + 1));
    vector<ll> tree(tree_size);
    vector<ll> lazy(tree_size);
	while (M--) {
		int O, S, T; cin >> O >> S >> T;
		if (O == 0) {
			update_range(tree, lazy, 1, 0, MAX_N - 1, S, T);
		} else {
			cout << query(tree, lazy, 1, 0, MAX_N - 1, S, T) << '\n';
		}
	}
    // init(a, tree, 1, 0, MAX_N - 1);
	// update_range(tree, lazy, 1, 0, MAX_N - 1, left - 1, right - 1, diff);
	// query(tree, lazy, 1, 0, MAX_N - 1, left - 1, right - 1);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}