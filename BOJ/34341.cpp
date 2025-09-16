#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
    int a, idx; ll v;
};

Node merge(Node a, Node b) {
    if (a.a < b.a) swap(a, b);
    if (a.a != b.a) return a;
    else {
        if (a.v < b.v) swap(a, b);
        return a;
    }
}

struct SegmentTree {
	vector<Node> arr;
	vector<Node> tree;
	int sz;

	SegmentTree() = default;
	SegmentTree(int _sz) {
        sz = _sz;
        arr.resize(sz);
        for (int i = 0; i < sz; ++i) arr[i] = Node {-1, -1, 0};
		int h = (int)ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<Node>(tree_size);
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
	void update(int node, int start, int end, int index, const Node& val) {
		if (index < start || index > end) return;
		if (start == end) {
			arr[index] = val;
			tree[node] = val;
			return;
		}
		int mid = (start + end) / 2;
		update(node * 2, start, mid, index, val);
		update(node * 2 + 1, mid + 1, end, index, val);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}
	Node query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return Node {-1, -1, 0};
		if (left <= start && end <= right) return tree[node];
		int mid = (start + end) / 2;
		Node lsum = query(node * 2, start, mid, left, right);
		Node rsum = query(node * 2 + 1, mid + 1, end, left, right);
		return merge(lsum, rsum);
	}
	void update(int index, Node val) { update(1, 0, sz - 1, index, val); }
	Node query(int left, int right) { return query(1, 0, sz - 1, left, right); }
};

int N;
int A[300002]; ll V[300002];
Node pfx[300002], sfx[300002][2];
vector<pair<int, int>> adj[300002];
multiset<pair<int, ll>> st[300002];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    A[0] = 0; A[N + 1] = 1e9; ++A[N + 1];
    for (int i = 1; i <= N; ++i) cin >> A[i];
    for (int i = 1; i <= N; ++i) cin >> V[i];
    vector<int> v;
    for (int i = 0; i <= N + 1; ++i) v.push_back(A[i]);
    sort(v.begin(), v.end());
    for (int i = 0; i <= N + 1; ++i) A[i] = lower_bound(v.begin(), v.end(), A[i]) - v.begin();
    SegmentTree seg {N + 2};
    for (int i = 0; i <= N + 1; ++i) {
        if (i == 0) pfx[i] = Node {0, -1, 0};
        else pfx[i] = seg.query(0, A[i] - 1);
        seg.update(A[i], Node {pfx[i].a + 1, i, pfx[i].v + V[i]});
    }
    seg = SegmentTree {N + 2};
    for (int i = N + 1; i >= 0; --i) {
        if (i == N + 1) sfx[i][0] = sfx[i][1] = Node {0, -1, 0};
        else {
            sfx[i][0] = seg.query(A[i] + 1, N + 1);
            
            auto tmp = seg.query(A[sfx[i][0].idx], A[sfx[i][0].idx]);
            seg.update(A[sfx[i][0].idx], Node {0, sfx[i][0].idx, 0});
            adj[sfx[i][0].idx].push_back(make_pair(i, 0));
            
            sfx[i][1] = seg.query(A[i] + 1, N + 1);
            adj[sfx[i][1].idx].push_back(make_pair(i, 1));
            seg.update(A[sfx[i][0].idx], tmp);

            // cout << sfx[i][0].idx << ' ' << sfx[i][1].idx << '\n';
        }
        seg.update(A[i], Node {sfx[i][0].a + 1, i, sfx[i][0].v + V[i]});
    }
    for (int i = 0; i <= N; ++i) {
        for (int t = 0; t < 2; ++t) {
            int j = sfx[i][t].idx;
            int a = pfx[i].a + sfx[i][t].a + 1;
            ll v = pfx[i].v + sfx[i][t].v + V[i];
            if (pfx[i].a + 1 == pfx[j].a) st[pfx[j].a].insert(make_pair(-a, -v));
            if (pfx[i].a + 2 == pfx[j].a) st[pfx[j].a].insert(make_pair(-a, -v));
            if (pfx[i].a + 2 == pfx[j].a) st[pfx[j].a - 1].insert(make_pair(-a, -v));
        }
    }
    for (int i = 1; i <= N; ++i) {
        for (auto [j, t]: adj[i]) {
            int a = pfx[j].a + sfx[j][t].a + 1;
            ll v = pfx[j].v + sfx[j][t].v + V[j];
            if (pfx[j].a + 1 == pfx[i].a) st[pfx[i].a].erase(st[pfx[i].a].find(make_pair(-a, -v)));
            if (pfx[j].a + 2 == pfx[i].a) st[pfx[i].a].erase(st[pfx[i].a].find(make_pair(-a, -v)));
        }
        
        cout << -st[pfx[i].a].begin()->second << ' ';
        for (auto [j, t]: adj[i]) {
            int a = pfx[j].a + sfx[j][t].a + 1;
            ll v = pfx[j].v + sfx[j][t].v + V[j];
            if (pfx[j].a + 1 == pfx[i].a) st[pfx[i].a].insert(make_pair(-a, -v));
            if (pfx[j].a + 2 == pfx[i].a) st[pfx[i].a].insert(make_pair(-a, -v));
        }
    }
}