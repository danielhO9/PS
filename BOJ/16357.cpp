#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void update_lazy(vector<ll>& tree, vector<ll>& lazy, int node, int start, int end) {
    if (lazy[node] != 0) {
        tree[node] += lazy[node];
        if (start != end) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

void update_range(vector<ll>& tree, vector<ll>& lazy, int node, int start, int end, int left, int right, ll diff) {
    update_lazy(tree, lazy, node, start, end);
    if (left > end || right < start) {
        return;
    }
    if (left <= start && end <= right) {
        tree[node] += diff;
        if (start != end) {
            lazy[node * 2] += diff;
            lazy[node * 2 + 1] += diff;
        }
        return;
    }
    update_range(tree, lazy, node * 2, start, (start + end) / 2, left, right, diff);
    update_range(tree, lazy, node * 2 + 1, (start + end) / 2 + 1, end, left, right, diff);
    tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
}

ll query(vector<ll>& tree, vector<ll>& lazy, int node, int start, int end, int left, int right) {
    update_lazy(tree, lazy, node, start, end);
    if (left > end || right < start) {
        return 0;
    }
    if (left <= start && end <= right) {
        return tree[node];
    }
    ll lsum = query(tree, lazy, node * 2, start, (start+end) / 2, left, right);
    ll rsum = query(tree, lazy, node * 2 + 1, (start+end) / 2 + 1, end, left, right);
    return max(lsum, rsum);
}

void solve() {
	int n; cin >> n;
	vector<pair<ll, ll>> lines;
	set<ll> S;
	for (int i = 0; i < n; ++i) {
		ll ux, uy, vx, vy;
		cin >> ux >> uy;
		cin >> vx >> vy;
		lines.push_back({vy, uy});
		lines.push_back({uy, vy});
		S.insert(vy); S.insert(uy);
	}
	sort(lines.begin(), lines.end(), [](auto& a, auto& b) {
		if (a.first == b.first) {
			return a.second > b.second;
		}
		return a.first < b.first;
	});
	// 0 ~ MAX_N - 1
	int MAX_N = S.size();
	ll num[MAX_N]; int temp = 0;
	unordered_map<ll, int> dict;
	for (auto i: S) {
		num[temp] = i;
		dict[i] = temp++;
	}
    vector<ll> a(MAX_N);
    int h = (int)ceil(log2(MAX_N));
    int tree_size = (1 << (h + 1));
    vector<ll> tree(tree_size);
    vector<ll> lazy(tree_size);
	for (auto i: lines) if (i.first < i.second) update_range(tree, lazy, 1, 0, MAX_N - 1, dict[i.first], dict[i.second], 1);
	ll ans = 0;
	int now = 0;
	ll ncnt = 0;
	for (int i = 0; i < MAX_N; ++i) {
		while (now < lines.size() && lines[now].first == num[i] && lines[now].first < lines[now].second) {
			// cout << lines[now].first << ' ' << lines[now].second << " in\n";
			update_range(tree, lazy, 1, 0, MAX_N - 1, dict[lines[now].first], dict[lines[now].second], -1);
			++now;
			++ncnt;
		}
		// cout << ncnt << '\n';
		ans = max(ans, ncnt + query(tree, lazy, 1, 0, MAX_N - 1, 0, MAX_N - 1));
		while (now < lines.size() && lines[now].first == num[i] && lines[now].first > lines[now].second) {
			// cout << lines[now].first << ' ' << lines[now].second << " out\n";
			update_range(tree, lazy, 1, 0, MAX_N - 1, dict[lines[now].second], dict[lines[now].first], 1);
			++now;
			--ncnt;
		}
		ans = max(ans, ncnt + query(tree, lazy, 1, 0, MAX_N - 1, 0, MAX_N - 1));
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}