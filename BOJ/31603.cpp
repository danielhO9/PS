#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INIT_VALUE = 0; // TODO

struct SegmentTree {
	vector<ll> arr;
	vector<ll> tree;
	int sz;

	ll merge(ll a, ll b) { return a + b; }
	SegmentTree() = default;
	SegmentTree(int sz): SegmentTree(vector<ll>(sz, INIT_VALUE)) {}
	SegmentTree(const vector<ll>& a) {
		sz = a.size();
		arr = a;
		int h = (int)ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<ll>(tree_size);
		init(1, 0, sz - 1);
	}
	void init(int node, int start, int end) {
		if (start == end) tree[node] = arr[start];
		else {
			int mid = (start + end) / 2;
			init(node * 2, start, mid);
			init(node * 2 + 1, mid + 1, end);
			tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
		}
	}
	void update(int node, int start, int end, int index, ll val) {
		if (index < start || index > end) return;
		if (start == end) {
			arr[index] += val;
			tree[node] += val;
			return;
		}
		int mid = (start + end) / 2;
		update(node * 2, start, mid, index, val);
		update(node * 2 + 1, mid + 1, end, index, val);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}
    ll query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return INIT_VALUE;
		if (left <= start && end <= right) return tree[node];
		int mid = (start + end) / 2;
		ll lsum = query(node * 2, start, mid, left, right);
		ll rsum = query(node * 2 + 1, mid + 1, end, left, right);
		return merge(lsum, rsum);
	}
    int kth(int node, int start, int end, ll k) {
        if (start == end) return start;
        ll tmp = tree[node * 2];
        int mid = (start + end) / 2;
        if (k <= tmp) return kth(node * 2, start, mid, k);
        else return kth(node * 2 + 1, mid + 1, end, k - tmp);
    }
	void update(int index, ll val) { update(1, 0, sz - 1, index, val); }
    ll query(int left, int right) { return query(1, 0, sz - 1, left, right); }
    int kth(ll k) { return kth(1, 0, sz - 1, k); }
} seg;

struct Node { int l, r; ll val; };

struct PST {
	vector<Node> tree;
	vector<int> root; // 1-index (0: dummy)
	int sz;

	PST() = default;
	PST(int sz): sz(sz) {
        tree.resize(1);
        root.resize(1);
	}
    // p에서 c로 분기
	void newRoot(int p, int c) {
        assert(p < root.size());
        while (root.size() <= c) root.push_back(0);
        root[c] = tree.size();
		tree.push_back(Node{tree[root[p]]});
        return;
	}
	void update(int node, int start, int end, int index, ll val) {
		if (index < start || index > end) return;
		tree[node].val += val;
		if (start == end) return;
		int mid = (start + end) / 2;
		if (index <= mid) {
			int lidx = tree[node].l;
			tree[node].l = tree.size();
			tree.push_back(Node{tree[lidx]});
			update(tree[node].l, start, mid, index, val);
		}
		if (index > mid) {
			int ridx = tree[node].r;
			tree[node].r = tree.size();
			tree.push_back(Node{tree[ridx]});
			update(tree[node].r, mid + 1, end, index, val);
		}
	}
    int kth(int l, int r, int start, int end, ll k) {
        if (start == end) return start;
        ll tmp = tree[tree[r].l].val - tree[tree[l].l].val;
        int mid = (start + end) / 2;
        if (tmp >= k) return kth(tree[l].l, tree[r].l, start, mid, k);
        else return kth(tree[l].r, tree[r].r, mid + 1, end, k - tmp);
    }
    int kth2(int l1, int r1, int l2, int r2, int start, int end, ll k) {
        if (start == end) return start;
        ll tmp = tree[tree[r1].l].val - tree[tree[l1].l].val - (tree[tree[r2].l].val - tree[tree[l2].l].val);
        int mid = (start + end) / 2;
        if (tmp >= k) return kth2(tree[l1].l, tree[r1].l, tree[l2].l, tree[r2].l, start, mid, k);
        else return kth2(tree[l1].r, tree[r1].r, tree[l2].r, tree[r2].r, mid + 1, end, k - tmp);
    }
    void update(int rt, int index, ll val) {
        assert(rt < root.size());
        update(root[rt], 0, sz - 1, index, val);
    }
    int kth(int l, int r, int k) {
        assert(l - 1 < root.size() && r < root.size());
        return kth(root[l - 1], root[r], 0, sz - 1, k);
    }
    int kth2(int l1, int r1, int l2, int r2, int k) {
        return kth2(root[l1 - 1], root[r1], root[l2 - 1], root[r2], 0, sz - 1, k);
    }
} pst;

struct Query {
    ll idx, lca, child, tar;
};

ll n, q;
ll p[100001], sz[100001], in[100001], out[100001], inv[100001];
int child[100001];
vector<int> adj[100001];
int rt;
vector<Query> query[100001];
int cnt = 0;

int dfs1(int v) {
    sz[v] = 1;
    in[v] = ++cnt;
    inv[in[v]] = v;
    for (auto u: adj[v]) sz[v] += dfs1(u);
    out[v] = cnt;
    return sz[v];
}

void dfs2(int v) {
    seg.update(v, sz[v]);
    for (auto& eq: query[v]) {
        eq.lca = seg.kth(eq.tar);
        eq.child = child[eq.lca];
        eq.tar -= seg.query(0, eq.lca - 1);
        // cout << v << ' ' << eq.lca << ' ' << eq.tar << '\n';
    }
    seg.update(v, -sz[v]);
    for (auto u: adj[v]) {
        seg.update(v, sz[v] - sz[u]);
        child[v] = u;
        dfs2(u);
        seg.update(v, -(sz[v] - sz[u]));
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
        if (p[i] == 0) rt = i;
        adj[p[i]].push_back(i);
    }
    dfs1(rt);
    seg = SegmentTree {(int) n + 1};
    for (int i = 0; i < q; ++i) {
        ll k; cin >> k;
        ll x = (k - 1) / n + 1;
        query[x].push_back(Query {i, x, 0, k - (x - 1) * n});
    }
    dfs2(rt);
    pst = PST {(int) n + 1};
    for (int i = 1; i <= n; ++i) {
        pst.newRoot(i - 1, i);
        pst.update(i, inv[i], 1);
    }
    vector<ll> ans(q);
    for (ll x = 1; x <= n; ++x) {
        for (auto& eq: query[x]) {
            ll y;
            if (x == eq.lca) y = pst.kth(in[x], out[x], eq.tar);
            else y = pst.kth2(in[eq.lca], out[eq.lca], in[eq.child], out[eq.child], eq.tar);
            ans[eq.idx] = (x - 1) * n * n + (eq.lca - 1) * n + (y - 1);
        }
    }
    for (auto i: ans) cout << i << '\n';   
}