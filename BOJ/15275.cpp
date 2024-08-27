#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
	ll x, y;
};

int n, m;
Point pt[200001];
int prv[200001], nxt[200001];

ll area(int i) {
	ll x[4] = {pt[prv[i]].x, pt[i].x, pt[nxt[i]].x, pt[prv[i]].x};
	ll y[4] = {pt[prv[i]].y, pt[i].y, pt[nxt[i]].y, pt[prv[i]].y};
	ll a = 0, b = 0;
	for (int i = 0; i < 3; ++i) a += x[i] * y[i + 1];
	for (int i = 0; i < 3; ++i) b += y[i] * x[i + 1];
	return abs(a - b);
}

void solve() {
	cin >> n >> m;
	for (int i = 0; i <= n; ++i) cin >> pt[i].x >> pt[i].y;
	for (int i = 1; i < n; ++i) {
		prv[i] = i - 1; nxt[i] = i + 1;
	}
	set<pair<ll, int>> s;
	for (int i = 1; i < n; ++i) s.insert({area(i), i});
	for (int i = 0; i < n - m; ++i) {
		auto [val, j] = *s.begin();
		s.erase({val, j});
		if (prv[j] > 0) s.erase({area(prv[j]), prv[j]});
		if (nxt[j] < n) s.erase({area(nxt[j]), nxt[j]});
		cout << j << '\n';
		nxt[prv[j]] = nxt[j];
		prv[nxt[j]] = prv[j];
		if (prv[j] > 0) s.insert({area(prv[j]), prv[j]});
		if (nxt[j] < n) s.insert({area(nxt[j]), nxt[j]});
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}