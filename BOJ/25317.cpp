#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int base = 1;

void init(vector<ll>& a, vector<ll>& tree, int node, int start, int end) {
	if (start == end) tree[node] = a[start];
	else {
		init(a, tree, node * 2, start, (start + end) / 2);
		init(a, tree, node * 2 + 1, (start + end) / 2 + 1, end);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}
}

void update(vector<ll>& a, vector<ll>& tree, int node, int start, int end, int index, ll val) {
	if (index < start || index > end) return;
	if (start == end) {
		a[index] = val;
		tree[node] = val;
		return;
	}
	update(a, tree, node * 2, start, (start + end) / 2, index, val);
	update(a, tree, node * 2 + 1, (start + end) / 2 + 1, end, index, val);
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll query(vector<ll>& tree, int node, int start, int end, int left, int right) {
	if (left > end || right < start) return 0;
	if (left <= start && end <= right) return tree[node];
	ll lsum = query(tree, node * 2, start, (start + end) / 2, left, right);
	ll rsum = query(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
	return lsum + rsum;
}

ll change(ll a, ll b) {
	double raw = (double) -(b * 2) / a;
	ll tmp = -(b * 2) / a;
	if (a * tmp == -b * 2) return tmp;
	if (tmp % 2 != 0) return tmp;
	if (raw < 0) return tmp - 1;
	return tmp + 1;
}

void solve() {
	int Q; cin >> Q;
	vector<pair<int, ll>> Query;
	vector<ll> nums;
	for (int i = 0; i < Q; ++i) {
		int t; cin >> t;
		if (t == 1) {
			ll a, b; cin >> a >> b;
			if (a == 0ll && b == 0ll) Query.push_back({3, 0ll});
			else if (a == 0ll) {
				if (b < 0ll) Query.push_back({3, -1ll});
			} else {
				if (a < 0ll) Query.push_back({3, -1ll});
				ll tmp = change(a, b);
				Query.push_back({1, tmp});
				nums.push_back(tmp);
			}
		} else {
			ll c; cin >> c;
			Query.push_back({2, 2 * c});
			nums.push_back(c * 2);
		}
	}
	sort(nums.begin(), nums.end());
	nums.erase(unique(nums.begin(), nums.end()), nums.end());
	// for (auto i: Query) {
	// 	cout << i.first << ' ' << i.second << '\n';
	// }
	unordered_map<ll, int> M;
	for (int i = 0; i < nums.size(); ++i) M[nums[i]] = i;
	// 0 ~ MAX_N - 1
	int MAX_N = nums.size();
	vector<ll> arr(MAX_N);
	int h = (int)ceil(log2(MAX_N));
	int tree_size = (1 << (h + 1));
	vector<ll> tree(tree_size);
	int cnt = 0;
	for (auto i: Query) {
		if (i.first == 1) {
			++cnt;
			update(arr, tree, 1, 0, MAX_N - 1, M[i.second], arr[M[i.second]] + 1);
		} else if (i.first == 2) {
			if (arr[M[i.second]] != 0) {
				cout << 0 << '\n';
				continue;
			}
			int tmp = query(tree, 1, 0, MAX_N - 1, 0, M[i.second]);
			tmp = cnt - tmp;
			int nbase = base;
			if (tmp % 2 == 1) nbase *= -1;
			if (nbase < 0) cout << '-';
			else if (nbase == 0) cout << 0;
			else cout << '+';
			cout << '\n';
		} else {
			base *= i.second;
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}