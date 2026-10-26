#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct custom_hash {
	static uint64_t splitmix64(uint64_t x) {
		// http://xorshift.di.unimi.it/splitmix64.c
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}

	size_t operator()(uint64_t x) const {
		static const uint64_t FIXED_RANDOM =
			chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x + FIXED_RANDOM);
	}
};

struct SegmentTree {
	vector<ll> arr;
	vector<ll> tree;
	int sz;

	inline ll merge(ll a, ll b) { return a + b; }

	void init(vector<ll> &a) {
		sz = a.size();
		arr = a;
		int h = (int)ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<ll>(tree_size);
		init(1, 0, sz - 1);
	}

	void init(int node, int start, int end) {
		if (start == end)
			tree[node] = arr[start];
		else {
			init(node * 2, start, (start + end) / 2);
			init(node * 2 + 1, (start + end) / 2 + 1, end);
			tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
		}
	}

	void update(int node, int start, int end, int index, ll val) {
		if (index < start || index > end)
			return;
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
		if (left > end || right < start)
			return 0; // modify
		if (left <= start && end <= right)
			return tree[node];
		ll lsum = query(node * 2, start, (start + end) / 2, left, right);
		ll rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		return merge(lsum, rsum);
	}

	void update(int index, ll val) { update(1, 0, sz - 1, index, val); }

	ll query(int left, int right) { return query(1, 0, sz - 1, left, right); }
};

int n;

void solve() {
	cin >> n;
	vector< pair<int, int> > pts(n);
	for (int i = 0; i < n; ++i)
		cin >> pts[i].first >> pts[i].second;
	set<int> xcor, ycor;
	for (int i = 0; i < n; ++i) {
		xcor.insert(pts[i].first);
		ycor.insert(pts[i].second);
	}
	unordered_map<int, int, custom_hash> xtoc, ytoc;
	int cnt = 0;
	for (auto i : xcor)
		xtoc[i] = cnt++;
	cnt = 0;
	for (auto i : ycor)
		ytoc[i] = cnt++;
	deque< pair<int, int> > vs(n);
	for (int i = 0; i < n; ++i)
		vs[i] = make_pair(xtoc[pts[i].first], ytoc[pts[i].second]);
	sort(vs.begin(), vs.end());
	vector<int> rx, ry;
	for (auto i : xcor)
		rx.push_back(i);
	for (auto i : ycor)
		ry.push_back(i);

	vector<ll> locnt(ycor.size(), 0);
	vector<ll> upcnt(ycor.size(), 0);
	int ucnt = n;
	for (int i = 0; i < n; ++i)
		++upcnt[vs[i].second];
	SegmentTree lseg, useg;
	lseg.init(locnt);
	useg.init(upcnt);
	ll ans = 0;
	int x = 0, y = 0;
	for (int i = 0; i < xcor.size(); ++i) {
		while (!vs.empty() && vs.front().first < i) {
			useg.update(vs.front().second, -1);
			--ucnt;
			lseg.update(vs.front().second, 1);
			vs.pop_front();
		}
		int l = 0, r = ycor.size(), mid;
		while (l + 1 < r) {
			mid = (l + r) / 2;
			int o, t, th, f;
			f = (mid == 0 ? 0 : useg.query(0,  mid - 1));
			o = ucnt - f;
			th = (mid == 0 ? 0 : lseg.query(0, mid - 1));
			t = (n - ucnt) - th;
			if (min(th, f) <= min(o, t)) l = mid;
			else r = mid;
		}
		int th, f;
		f = (l == 0 ? 0 : useg.query(0,  l - 1));
		th = (l == 0 ? 0 : lseg.query(0, l - 1));
		if (ans < min(th, f)) {
			ans = min(th, f);
			x = i; y = l;
		}
		++l;
		if (l == ycor.size()) continue;
		int o, t;
		f = (l == 0 ? 0 : useg.query(0,  l - 1));
		o = ucnt - f;
		th = (l == 0 ? 0 : lseg.query(0, l - 1));
		t = (n - ucnt) - th;
		if (ans < min(o, t)) {
			ans = min(o, t);
			x = i; y = l;
		}
	}
	cout << ans << '\n';
	cout << rx[x] << ' ' << ry[y] << '\n';
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	while (t--)
		solve();
}