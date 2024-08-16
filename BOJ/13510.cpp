#include <bits/stdc++.h>
using namespace std;

vector<int> arr, tree;
int N;

void init(vector<int>& a, vector<int>& tree, int node, int start, int end) {
	if (start == end) tree[node] = a[start];
	else {
		init(a, tree, node * 2, start, (start + end) / 2);
		init(a, tree, node * 2 + 1, (start + end) / 2 + 1, end);
		tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
	}
}

void update(vector<int>& a, vector<int>& tree, int node, int start, int end, int index, int val) {
	if (index < start || index > end) return;
	if (start == end) {
		a[index] = val;
		tree[node] = val;
		return;
	}
	update(a, tree, node * 2, start, (start + end) / 2, index, val);
	update(a, tree, node * 2 + 1, (start + end) / 2 + 1, end, index, val);
	tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
}

int query1(vector<int>& tree, int node, int start, int end, int left, int right) {
	if (left > end || right < start) return 0;
	if (left <= start && end <= right) return tree[node];
	int lsum = query1(tree, node * 2, start, (start + end) / 2, left, right);
	int rsum = query1(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
	return max(lsum, rsum);
}

const int MAX_V = 200001;
int sz[MAX_V], dep[MAX_V], par[MAX_V], top[MAX_V], in[MAX_V], out[MAX_V];
vector<int> adj[MAX_V];

void dfs1(int v = 1, int p = 0) {
	sz[v] = 1;
	for (auto& i: adj[v]) if (i != p) {
		dep[i] = dep[v] + 1; par[i] = v;
		dfs1(i, v); sz[v] += sz[i];
		if (sz[i] > sz[adj[v][0]]) swap(i, adj[v][0]);
	}
}

int pv = -1;
void dfs2(int v = 1, int p = 0) {
	in[v] = ++pv;
	if (v == 1) top[v] = v;
	for (auto i: adj[v]) if (i != p) {
		top[i] = i == adj[v][0] ? top[v] : i;
		dfs2(i, v);
	}
	out[v] = pv;
}

int query2(int a, int b) {
    int ret = 0;
    while(top[a] ^ top[b]){
        if(dep[top[a]] < dep[top[b]]) swap(a, b);
        int st = top[a];
        ret = max(ret, query1(tree, 1, 0, N, in[st], in[a]));
        a = par[st];
    }
    if(dep[a] > dep[b]) swap(a, b);
    ret = max(ret, query1(tree, 1, 0, N, in[a] + 1, in[b]));
    return ret;
}

void solve() {
	cin >> N; int Q; cin >> Q;
	for (int i = 2; i <= N; ++i) {
		int u; cin >> u;
		adj[u].push_back(i);
	}
	dfs1(); dfs2();
	arr = vector<int>(N + 1);
	int h = (int)ceil(log2(N + 1));
	int tree_size = (1 << (h + 1));
	tree = vector<int> (tree_size);
	while (Q--) {
		int b, c, d; cin >> b >> c >> d;
		if (d == 0) {
			if (query2(b, c) == 0) cout << "YES\n";
			else cout << "NO\n";
		} else {
			if (query2(b, c) == 0) {
				cout << "YES\n";
				update(arr, tree, 1, 0, N, in[b], 1);
			} else {
				cout << "NO\n";
				update(arr, tree, 1, 0, N, in[c], 1);
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}