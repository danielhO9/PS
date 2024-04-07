#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

void init(vector<ll>& a, vector<ll>& tree, int node, int start, int end) {
    if (start == end) {
        tree[node] = a[start];
    } else {
        init(a, tree, node * 2, start, (start + end) / 2);
        init(a, tree, node * 2 + 1, (start + end) / 2 + 1, end);
        tree[node] = (tree[node * 2] + tree[node * 2 + 1]) % MOD;
    }
}

void update_lazy(vector<ll>& tree, vector<pair<ll, ll>>& lazy, int node, int start, int end) {
    if (lazy[node].first != 1 || lazy[node].second != 0) {

        tree[node] = ((tree[node] * lazy[node].first) % MOD + ((end - start + 1) * lazy[node].second) % MOD) % MOD;
        if (start != end) {
            lazy[node * 2] = {(lazy[node].first * lazy[node * 2].first) % MOD, ((lazy[node].first * lazy[node * 2].second) % MOD + lazy[node].second) % MOD};
            lazy[node * 2 + 1] = {(lazy[node].first * lazy[node * 2 + 1].first) % MOD, ((lazy[node].first * lazy[node * 2 + 1].second) % MOD + lazy[node].second) % MOD};
        }

        lazy[node] = {1, 0};
    }
}

void update_range(vector<ll>& tree, vector<pair<ll, ll>>& lazy, int node, int start, int end, int left, int right, ll diff, int type) {
    update_lazy(tree, lazy, node, start, end);
    if (left > end || right < start) {
        return;
    }
    if (left <= start && end <= right) {
		if (type == 1) tree[node] += ((end - start + 1) * diff) % MOD;
		if (type == 2) tree[node] *= diff;
		if (type == 3) tree[node] = ((end - start + 1) * diff) % MOD;
		tree[node] %= MOD;
        if (start != end) {
			if (type == 1) {
				lazy[node * 2].second = (lazy[node * 2].second + diff) % MOD;
				lazy[node * 2 + 1].second = (lazy[node * 2 + 1].second + diff) % MOD;
			}
			if (type == 2) {
				lazy[node * 2].first = (lazy[node * 2].first * diff) % MOD;
				lazy[node * 2].second = (lazy[node * 2].second * diff) % MOD;
				lazy[node * 2 + 1].first = (lazy[node * 2 + 1].first * diff) % MOD;
				lazy[node * 2 + 1].second = (lazy[node * 2 + 1].second * diff) % MOD;
			}
            if (type == 3) {
				lazy[node * 2].first = 0;
				lazy[node * 2].second = diff;
				lazy[node * 2 + 1].first = 0;
				lazy[node * 2 + 1].second = diff;
			}
        }
        return;
    }
    update_range(tree, lazy, node * 2, start, (start + end) / 2, left, right, diff, type);
    update_range(tree, lazy, node * 2 + 1, (start + end) / 2 + 1, end, left, right, diff, type);
    tree[node] = (tree[node * 2] + tree[node * 2 + 1]) % MOD;
}

ll query(vector<ll>& tree, vector<pair<ll, ll>>& lazy, int node, int start, int end, int left, int right) {
    update_lazy(tree, lazy, node, start, end);
    if (left > end || right < start) {
        return 0;
    }
    if (left <= start && end <= right) {
        return tree[node];
    }
    ll lsum = query(tree, lazy, node * 2, start, (start+end) / 2, left, right);
    ll rsum = query(tree, lazy, node * 2 + 1, (start+end) / 2 + 1, end, left, right);
    return (lsum + rsum) % MOD;
}

void solve() {
	int N; cin >> N;
	// 0 ~ MAX_N - 1
	int MAX_N = N;
    vector<ll> a(MAX_N); for (int i = 0; i < N; ++i) cin >> a[i];
    int h = (int)ceil(log2(MAX_N));
    int tree_size = (1 << (h + 1));
    vector<ll> tree(tree_size);
    vector<pair<ll, ll>> lazy(tree_size);
	for (auto& i: lazy) i = {1, 0};
    init(a, tree, 1, 0, MAX_N - 1);
	int M; cin >> M;
	while (M--) {
		int what, x, y; cin >> what >> x >> y; --x; --y;
		if (what == 4) cout << query(tree, lazy, 1, 0, MAX_N - 1, x, y) << '\n';
		else {
			ll v; cin >> v;
			update_range(tree, lazy, 1, 0, MAX_N - 1, x, y, v, what);
		}
	}
	// update_range(tree, lazy, 1, 0, MAX_N - 1, left - 1, right - 1, diff);
	// query(tree, lazy, 1, 0, MAX_N - 1, left - 1, right - 1);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}