#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Line {
	int b, t, type;
};

ll sum(vector<ll> &tree, int i) {
    ll ans = 0;
    while (i > 0) {
        ans += tree[i];
        i -= (i & -i);
    }
    return ans;
}
void update(vector<ll> &tree, int i, ll diff) {
    while (i < tree.size()) {
        tree[i] += diff;
        i += (i & -i);
    }
}

void solve() {
	int N, M; cin >> N >> M;
	vector<pair<int, int>> eggs;
	for (int i = 0; i < N; ++i) {
		int x, y; cin >> x >> y;
		eggs.push_back({x, y});
	}
	vector<pair<int, Line>> V;
	for (int i = 0; i < M; ++i) {
		int l, r, b, t; cin >> l >> r >> b >> t;
		V.push_back({l, {b, t, 1}});
		V.push_back({r, {b, t, -1}});
	}
	sort(eggs.begin(), eggs.end());
	sort(V.begin(), V.end(), [](auto& a, auto& b) {
		if (a.first == b.first) return a.second.type > b.second.type;
		return a.first < b.first;
	});
	int n; n = 1e5 + 1;
	// 1 ~ n
	vector<ll> a(n + 1);
    vector<ll> tree(n + 1);
	int negg = 0, np = 0, ans = 0;
	for (int i = 0; i <= 1e5; ++i) {
		while (np < V.size() && V[np].first == i && V[np].second.type == 1) {
			// cout << np << '\n';
			update(tree, V[np].second.b + 1, 1);
			if (V[np].second.t + 2 < n + 1) update(tree, V[np].second.t + 2, -1);
			++np;
		}
		while (negg < eggs.size() && eggs[negg].first == i) {
			ans += sum(tree, eggs[negg].second + 1);
			++negg;
		}
		while (np < V.size() && V[np].first == i && V[np].second.type == -1) {
			// cout << np << '\n';
			update(tree, V[np].second.b + 1, -1);
			if (V[np].second.t + 2 < n + 1) update(tree, V[np].second.t + 2, 1);
			++np;
		}
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}