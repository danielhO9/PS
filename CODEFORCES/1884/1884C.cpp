#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void update_lazy(vector<LL> &tree, vector<LL> &lazy, int node, int start, int end) {
    if (lazy[node] != 0) {
        tree[node] += lazy[node];
        if (start != end) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

void update_range(vector<LL> &tree, vector<LL> &lazy, int node, int start, int end, int left, int right, LL diff) {
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
    tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
}

LL query(vector<LL> &tree, vector<LL> &lazy, int node, int start, int end, int left, int right) {
    update_lazy(tree, lazy, node, start, end);
    if (left > end || right < start) {
        return LLONG_MAX;
    }
    if (left <= start && end <= right) {
        return tree[node];
    }
    LL lsum = query(tree, lazy, node * 2, start, (start+end) / 2, left, right);
    LL rsum = query(tree, lazy, node * 2 + 1, (start+end) / 2 + 1, end, left, right);
    return min(lsum, rsum);
}

void solve() {
	int n, m; cin >> n >> m;
	int l[n], r[n];
	set<int> S;
	for (int i = 0; i < n; ++i) {
		cin >> l[i] >> r[i];
		S.insert(l[i]); S.insert(r[i]);
	}
	S.insert(1); S.insert(m);
	int cnt = S.size(); map<int, int> M;
	int index = 0; 
	for (auto i: S) M[i]= index++;
	for (int i = 0; i < n; ++i) {
		l[i] = M[l[i]];
		r[i] = M[r[i]];
	}
	deque<pair<int, int>> V;
	for (int i = 0; i < n; ++i) V.push_back({l[i], r[i]});
	sort(V.begin(), V.end());
	// cout << '\n';
	// for (auto i: V) {
	// 	cout << i.first << ' ' << i.second << '\n';
	// }
	// cout << '\n';
	int maxValue = 0, ans = 0;
	int h = (int)ceil(log2(cnt));
    int tree_size = (1 << (h + 1));
    vector<LL> tree(tree_size);
    vector<LL> lazy(tree_size);
	// r, l 오름차순
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
	for (int i = 0; i < cnt; ++i) {
		while (!Q.empty()) {
			pair<int, int> t = Q.top();
			if (t.first >= i) break;
			update_range(tree, lazy, 1, 0, cnt - 1, t.second, t.first, -1);
			Q.pop(); --maxValue;
		}
		while (!V.empty()) {
			pair<int, int> t = V.front();
			if (t.first > i) break;
			Q.push({t.second, t.first});
			update_range(tree, lazy, 1, 0, cnt - 1, t.first, t.second, 1);
			V.pop_front(); ++maxValue;
		}
		int minValue = query(tree, lazy, 1, 0, cnt - 1, 0, cnt - 1);
		ans = max(ans, maxValue - minValue);
		// cout << maxValue << ' ' << minValue << '\n';
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}

/*
1
7 6
2 2
1 6
1 2
5 6
1 5
4 4
3 6
*/