#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
	ll y1, y2, t;
};

vector<ll> ycor;
unordered_map<int, int> yM;
vector<ll> xcor;
vector<vector<Point>> todo;
vector<pair<int, Point>> V;
set<int> S;
vector<ll> tree(1048576);
vector<ll> lazy(1048576);
vector<ll> val(1048576);

void update_lazy(int node, int start, int end) {
    if (lazy[node] != 0) {
        tree[node] += lazy[node];
		if (start != end) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
		if (tree[node] == 0) {
			if (start == end) { val[node] = 0; return; }
			update_lazy(node * 2, start, (start + end) / 2);
			update_lazy(node * 2 + 1, (start + end) / 2 + 1, end);
			val[node] = val[node * 2] + val[node * 2 + 1];
		}
		else val[node] = ycor[end + 1] - ycor[start];
    }
}

void update_range(int node, int start, int end, int left, int right, ll diff) {
    update_lazy(node, start, end);
    if (left > end || right < start) {
        return;
    }
    if (left <= start && end <= right) {
        tree[node] += diff;
        if (start != end) {
            lazy[node * 2] += diff;
            lazy[node * 2 + 1] += diff;
        }
		if (tree[node] == 0) {
			if (start == end) { val[node] = 0; return; }
			update_lazy(node * 2, start, (start + end) / 2);
			update_lazy(node * 2 + 1, (start + end) / 2 + 1, end);
			val[node] = val[node * 2] + val[node * 2 + 1];
		}
		else val[node] = ycor[end + 1] - ycor[start];
        return;
    }
    update_range(node * 2, start, (start + end) / 2, left, right, diff);
    update_range(node * 2 + 1, (start + end) / 2 + 1, end, left, right, diff);
    tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
	if (tree[node] == 0) val[node] = val[node * 2] + val[node * 2 + 1];
	else val[node] = ycor[end + 1] - ycor[start];
}

void solve() {
	int n; cin >> n;
	for (int i = 0; i < n; ++i) {
		int x1, x2, y1, y2; cin >> x1 >> x2 >> y1 >> y2;
		V.push_back({x1, {y1, y2, 1}});
		V.push_back({x2, {y1, y2, -1}});
		S.insert(y1); S.insert(y2);
	}
	sort(V.begin(), V.end(), [](auto& a, auto& b) { return a.first < b.first; });
	for (auto i: S) {
		yM[i] = ycor.size();
		ycor.push_back(i);
	}
	S.clear();
	for (auto i: V) {
		if (xcor.empty() || xcor.back() != i.first) {
			xcor.push_back(i.first);
			todo.push_back({});
		}
		todo.back().push_back(i.second);
	}
	V.clear(); V.shrink_to_fit();
	// 0 ~ n - 1
	n *= 2;
	ll ans = 0;
	for (int i = 0; i < todo.size(); ++i) {
		if (i != 0) {
			ll temp = xcor[i] - xcor[i - 1];
			temp *= val[1];
			ans += temp;
		}
		for (auto j: todo[i]) {
			// cout << yM[j.y1] << ' ' << yM[j.y2] - 1 << ' ' <<  j.t << ' ';
			update_range(1, 0, n - 1, yM[j.y1], yM[j.y2] - 1, j.t);
			// for (auto k: val) cout << k << ' ';
		}
		// cout << val[1] << ' ';
		// cout << ans << '\n';
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}