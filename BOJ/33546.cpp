#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct SegmentTree {
	vector<pair<ll, ll>> tree;
	int sz;

	inline pair<ll, ll> merge(pair<ll, ll>& a, pair<ll, ll>& b) { return make_pair(a.first + b.first, a.second + b.second); }

	void init(int _sz) {
		sz = _sz;
		int h = (int)ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<pair<ll, ll>>(tree_size, {0, 0});
	}

	void update(int node, int start, int end, int index, ll val) {
		if (index < start || index > end) return;
		if (start == end) {
			++tree[node].first;
			tree[node].second += val; // modify
			return;
		}
		update(node * 2, start, (start + end) / 2, index, val);
		update(node * 2 + 1, (start + end) / 2 + 1, end, index, val);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}

	pair<ll, ll> query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return make_pair(0, 0); // modify
		if (left <= start && end <= right) return tree[node];
		pair<ll, ll> lsum = query(node * 2, start, (start + end) / 2, left, right);
		pair<ll, ll> rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		return merge(lsum, rsum);
	}

	void update(int index, ll val) { update(1, 0, sz - 1, index, val); }

	pair<ll, ll> query(int left, int right) { return query(1, 0, sz - 1, left, right); }
} seg;

struct Query {
	ll a, b, c, idx;
};

struct Point {
	ll x, y, t, idx;
};

ll N, Q;
ll A[250000], B[250000], C[250000];
ll ans[250000];
vector<Query> q;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> A[i] >> B[i] >> C[i];
	cin >> Q;
	ll a = 0, b = 0, c = 0;
	for (int i = 0; i < Q; ++i) {
		char ch; ll X; cin >> ch >> X;
		if (ch == 'A') a += X;
		else if (ch == 'B') b += X;
		else c += X;
		q.push_back({a, b, c, i});
	}
	ll smC = 0; for (int i = 0; i < N; ++i) smC += C[i];
	for (int i = 0; i < Q; ++i) ans[i] = smC + q[i].c * N;
	vector<Point> p;
	for (int i = 0; i < N; ++i) p.push_back({B[i] - A[i], C[i] - A[i], 0, i});
	for (int i = 0; i < Q; ++i) p.push_back({q[i].a - q[i].b, q[i].a - q[i].c, 1, i});
	sort(p.begin(), p.end(), [](const Point& a, const Point& b) { return tie(a.y, a.x, a.t) < tie(b.y, b.x, b.t); });
	set<ll> s; for (auto& i: p) s.insert(i.x);
	unordered_map<ll, int> m;
	int sz = 0;
	for (auto i: s) m[i] = sz++;
	seg.init(sz);
	for (auto& pt: p) {
		if (pt.t == 1) {
			pair<ll, ll> val; int xidx = m[pt.x];
			val = seg.query(0, xidx);
			ans[pt.idx] += val.second + (q[pt.idx].a - q[pt.idx].c) * val.first;
		} else {
			int xidx = m[pt.x];
			seg.update(xidx, A[pt.idx] - C[pt.idx]);
		}
	}
	
	p.clear();
	for (int i = 0; i < N; ++i) p.push_back({A[i] - B[i], C[i] - B[i], 0, i});
	for (int i = 0; i < Q; ++i) p.push_back({q[i].b - q[i].a, q[i].b - q[i].c, 1, i});
	sort(p.begin(), p.end(), [](const Point& a, const Point& b) { return tie(a.y, a.x, a.t) < tie(b.y, b.x, b.t); });
	s.clear(); for (auto& i: p) s.insert(i.x);
	m.clear(); sz = 0;
	for (auto i: s) m[i] = sz++;
	seg.init(sz);
	for (auto& pt: p) {
		if (pt.t == 1) {
			pair<ll, ll> val; int xidx = m[pt.x];
			if (xidx == 0) val = make_pair(0, 0);
			else val = seg.query(0, xidx - 1);
			ans[pt.idx] += val.second + (q[pt.idx].b - q[pt.idx].c) * val.first;
		} else {
			int xidx = m[pt.x];
			seg.update(xidx, B[pt.idx] - C[pt.idx]);
		}
	}

	for (int i = 0; i < Q; ++i) cout << ans[i] << '\n';
}

/*
Ai + aj >= Bi + bj
Ai + aj >= Ci + cj

aj - bj >= Bi - Ai
aj - cj >= Ci - Ai
-> Qj += Ai + aj

Bi + bj > Ai + aj
Bi + bj >= Ci + cj
bj - aj > Ai - Bi
bj - cj >= Ci - Bi

prv: Ci + cj


1 '6' 5
4 '5' 3

1 '6' 6
4 '5' 4

3 '6' 6
'6' 5 4



*/