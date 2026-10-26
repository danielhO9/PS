#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct SegmentTree {
	vector<ll> arr;
	vector<ll> tree;
	int sz;

	inline ll merge(ll a, ll b) { return a + b; }

	void init(vector<ll>& a) {
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
			init(node * 2, start, (start + end) / 2);
			init(node * 2 + 1, (start + end) / 2 + 1, end);
			tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
		}
	}

	void update(int node, int start, int end, int index, ll val) {
		if (index < start || index > end) return;
		if (start == end) {
			arr[index] += val; // modify
			tree[node] += val; // modify
			return;
		}
		update(node * 2, start, (start + end) / 2, index, val);
		update(node * 2 + 1, (start + end) / 2 + 1, end, index, val);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}

	ll query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return 0; // modify
		if (left <= start && end <= right) return tree[node];
		ll lsum = query(node * 2, start, (start + end) / 2, left, right);
		ll rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		return merge(lsum, rsum);
	}

	void update(int index, ll val) { update(1, 0, sz - 1, index, val); }

	ll query(int left, int right) { return query(1, 0, sz - 1, left, right); }
} seg;

int N, Q;
int A[200000];

void solve() {
	cin >> N >> Q;
	for (int i = 0; i < N; ++i) cin >> A[i];
	deque<pair<pair<int, int>, int>> query;
	for (int i = 0; i < Q; ++i) {
		int R, X; cin >> R >> X;
		query.push_back({{R, X}, i});
	}
	sort(query.begin(), query.end(), [](const pair<pair<int, int>, int>& a, const pair<pair<int, int>, int>& b) {
		return a.first.first < b.first.first;
	});
	set<int> s;
	unordered_map<int, int> m;
	for (int i = 0; i < N; ++i) s.insert(A[i]);
	for (int i = 0; i < Q; ++i) s.insert(query[i].first.second);
	int cnt = 0;
	for (auto i: s) m[i] = cnt++;
	vector<int> cur;
	vector<pair<int, int>> range(N);
	for (int i = 0; i < N; ++i) {
		if (cur.empty()) {
			range[i] = {m[A[i]], cnt};
			cur.push_back(A[i]);
		} else {
			auto itr = lower_bound(cur.begin(), cur.end(), A[i]) - cur.begin();
			if (itr == cur.size()) {
				range[i] = {m[A[i]], cnt};
				cur.push_back(A[i]);
			} else {
				range[i] = {m[A[i]], m[cur[itr]]};
				cur[itr] = A[i];
			}
		}
		// cout << range[i].first << ' ' << range[i].second << '\n';
	}
	vector<ll> arr(cnt, 0); seg.init(arr);
	vector<int> ans(Q);
	for (int i = 0; i < N; ++i) {
		seg.update(range[i].first, 1);
		if (range[i].second < cnt) seg.update(range[i].second, -1);
		while (!query.empty() && query.front().first.first - 1 == i) {
			int x = query.front().first.second;
			ans[query.front().second] = seg.query(0, m[x]);
			query.pop_front();
		}
	}
	for (auto i: ans) cout << i << '\n';
	
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}