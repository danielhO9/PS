#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const double EPS = 1e-8;

// y = ax + b
struct Line {
	mutable ll a, b;
    mutable double p;
    bool operator== (const Line& o) const { return a == o.a && b == o.b && abs(p - o.p) < EPS; }
	bool operator< (const Line& o) const { return a < o.a; }
	bool operator< (const ll x) const { return p < x; }
};

// maximum
struct LineContainer : multiset<Line, less<>> {
	double div(ll a, ll b) { return (double) a / b; }
	bool bad(iterator x, iterator y,  stack<pair<Line, bool>>& st) {
        st.push(make_pair(*x, 0));
		if (y == end()) return x->p = LLONG_MAX, false;
		if (x->a == y->a) x->p = x->b > y->b ? LLONG_MAX : LLONG_MIN;
		else x->p = div(y->b - x->b, x->a - y->a);
        st.push(make_pair(*x, 1));
		return x->p >= y->p;
	}
	void add(ll a, ll b, stack<pair<Line, bool>>& st) {
		auto z = insert({a, b, 0}), y = z++, x = y;
        st.push(make_pair(Line{a, b, 0}, 1));
		while (bad(y, z, st)) {
            st.push(make_pair(*z, 0));
            z = erase(z);
        }
		if (x != begin() && bad(--x, y, st)) bad(x, erase(y), st);
		while ((y = x) != begin() && (--x)->p >= y->p) {
            st.push(make_pair(*y, 0));
            bad(x, erase(y), st);
        }
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.a * x + l.b;
	}
} cht;

struct Edge {
	ll a, b;
	int s, e;
};

int n;
vector<vector<Edge>> tree;
vector<int> query;

void update(int node, int start, int end, const Edge& e) {
	if (e.s > end || e.e < start) return;
    if (e.s <= start && end <= e.e) {
        tree[node].push_back(e);
        return;
    }
	int mid = (start + end) / 2;
    update(node * 2, start, mid, e);
    update(node * 2 + 1, mid + 1, end, e);
}

void dnc(int node, int start, int end) {
	stack<pair<Line, bool>> st;
	for (const auto& e: tree[node]) cht.add(e.a, e.b, st);
	if (start == end) {
		if (cht.empty()) cout << "EMPTY\n";
		else cout << cht.query(query[start]) << '\n';
	} else {
		int mid = (start + end) / 2;
		dnc(node * 2, start, mid);
		dnc(node * 2 + 1, mid + 1, end);
	}
	while (!st.empty()) {
		const auto e = st.top(); st.pop();
		if (e.second) cht.erase(e.first);
		else cht.insert(e.first);
	}
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	vector<Edge> input(n, Edge {0, 0, -1, -1});
	for (int i = 0; i < n; ++i) {
		int t; cin >> t;
		if (t == 1) {
			cin >> input[i].a >> input[i].b;
			input[i].s = query.size();
		}
		else if (t == 2) {
			int idx; cin >> idx; --idx;
			input[idx].e = query.size();
			if (input[idx].e == 0) input[idx].s = -1;
			--input[idx].e;
		} else {
			ll x; cin >> x;
			query.push_back(x);
		}
	}
	int Q = query.size();
	int h = (int) ceil(log2(Q));
	int tree_size = (1 << (h + 1));
	tree.resize(tree_size);
	for (int i = 0; i < n; ++i) if (input[i].s >= 0) {
		if (input[i].e == -1) input[i].e = Q - 1;
		update(1, 0, Q - 1, input[i]);
	}
	dnc(1, 0, Q - 1);
}