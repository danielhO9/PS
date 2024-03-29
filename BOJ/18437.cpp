#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void init(vector<ll>& a, vector<ll>& tree, int node, int start, int end) {
    if (start == end) {
        tree[node] = a[start];
    } else {
        init(a, tree, node * 2, start, (start + end) / 2);
        init(a, tree, node * 2 + 1, (start + end) / 2 + 1, end);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }
}

void update_lazy(vector<ll>& tree, vector<ll>& lazy, int node, int start, int end) {
    if (lazy[node] != -1) {
		tree[node] = (end - start + 1) * lazy[node];
		if (start != end) {
			lazy[node * 2] = lazy[node];
			lazy[node * 2 + 1] = lazy[node];
		}
		lazy[node] = -1;
	}
}

void update_range(vector<ll>& tree, vector<ll>& lazy, int node, int start, int end, int left, int right, ll val) {
	if (left > right) return;
    update_lazy(tree, lazy, node, start, end);
    if (left > end || right < start) {
        return;
    }
    if (left <= start && end <= right) {
        tree[node] = (end - start + 1) * val;
        if (start != end) {
            lazy[node * 2] = val;
            lazy[node * 2 + 1] = val;
        }
        return;
    }
    update_range(tree, lazy, node * 2, start, (start + end) / 2, left, right, val);
    update_range(tree, lazy, node * 2 + 1, (start + end) / 2 + 1, end, left, right, val);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll query(vector<ll>& tree, vector<ll>& lazy, int node, int start, int end, int left, int right) {
	if (left > right) return 0;
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

int in[100001], out[100001], cnt = -1;
vector<int> adj[100001];
void dfs(int v, int p) {
	in[v] = ++cnt;
	for (int u: adj[v]) if (u != p) dfs(u, v);
	out[v] = cnt;
}

void solve() {
	int N; cin >> N;
	for (int i = 1; i <= N; ++i) {
		int p; cin >> p;
		adj[i].push_back(p);
		adj[p].push_back(i);
	}
	dfs(1, 0);
	int M; cin >> M;
	// 0 ~ MAX_N - 1
	int MAX_N = N;
    vector<ll> a(MAX_N, 1);
    int h = (int)ceil(log2(MAX_N));
    int tree_size = (1 << (h + 1));
    vector<ll> tree(tree_size);
    vector<ll> lazy(tree_size, -1);
	init(a, tree, 1, 0, MAX_N - 1);
	while (M--) {
		int what, i; cin >> what >> i;
		if (what == 1) {
			update_range(tree, lazy, 1, 0, MAX_N - 1, in[i] + 1, out[i], 1);
		} else if (what == 2) {
			update_range(tree, lazy, 1, 0, MAX_N - 1, in[i] + 1, out[i], 0);
		} else {
			cout << query(tree, lazy, 1, 0, MAX_N - 1, in[i] + 1, out[i]) << '\n';
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