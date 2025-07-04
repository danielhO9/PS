#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007;

struct MergeSortTree {
	vector<ll> arr;
	vector<vector<ll>> tree;
	int sz;

	MergeSortTree(vector<ll>& a) {
		sz = a.size();
		arr = a;
		int h = (int)ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<vector<ll>>(tree_size);
		init(1, 0, sz - 1);
	}
	void init(int node, int start, int end) {
		if (start == end) tree[node].push_back(arr[start]);
		else {
			int mid = (start + end) / 2;
			init(node * 2, start, mid);
			init(node * 2 + 1, mid + 1, end);
			tree[node].resize(tree[node * 2].size() + tree[node * 2 + 1].size());
			merge(tree[node * 2].begin(), tree[node * 2].end(), tree[node * 2 + 1].begin(), tree[node * 2 + 1].end(), tree[node].begin());
		}
	}
	// # of element <= k
	ll query(int node, int start, int end, int left, int right, ll k) {
		if (left > end || right < start) return 0;
		if (left <= start && end <= right) return upper_bound(tree[node].begin(), tree[node].end(), k) - tree[node].begin();
		ll lcnt = query(node * 2, start, (start + end) / 2, left, right, k);
		ll rcnt = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right, k);
		return lcnt + rcnt;
	}
	ll query(int left, int right, ll k) { return query(1, 0, sz - 1, left, right, k); }
};

int cnt = -1;
int s[200001], e[200001];
vector<int> adj[200001];
int c[200001];
int N, M, C;

void dfs(int v, int p) {
    s[v] = ++cnt;
    for (auto u: adj[v]) if (u != p) dfs(u, v);
    e[v] = cnt;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M >> C;
    for (int i = 1; i <= N; ++i) cin >> c[i];
    for (int i = 0; i < N - 1; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    vector<ll> a(N);
    for (int i = 1; i <= N; ++i) a[s[i]] = c[i];
    MergeSortTree seg {a};
    ll ans = 0;
    while (M--) {
        int v, col; cin >> v >> col;
        ans += seg.query(s[v], e[v], col);
        ans %= MOD;
    }
    cout << ans;
}