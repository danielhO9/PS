#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
ll a[500001];
int ord[500001];
ll ans[500001];

void update(int l, int r, ll val) {
	l = max(l, 0);
	r = min(r, n);
	if (l > r) return;
	ans[l] += val;
	ans[r] -= val;
}

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		ord[i] = i;
		ans[i] = 0ll;
	}
	sort(ord, ord + n, [](int i, int j){
		return a[i] < a[j];
	});
	set<int> s;
	s.insert(-1);
	s.insert(-2);
	s.insert(n);
	s.insert(n + 1);
	for (int i = 0; i < n; ++i) {
		s.insert(ord[i]);
		auto here = s.lower_bound(ord[i]);
		int x = *here;
		int l = *(prev(here));
		int r = *(next(here));
		int ll = *(prev(prev(here)));
		int rr = *(next(next(here)));
		update(0, l, a[x] * (r - x) * (x - l));
		update(l, l + 1, a[x] * (r - x) * (x - ll - 1));
		update(l + 1, x, a[x] * (r - x) * (x - l - 1));
		update(x + 1, r, a[x] * (x - l) * (r - x - 1));
		update(r, r + 1, a[x] * (x - l) * (rr - x - 1));
		update(r + 1, n, a[x] * (x - l) * (r - x));
	}
	for (int i = 1; i < n; ++i) ans[i] += ans[i - 1];
	for (int i = 0; i < n; ++i) cout << ans[i] << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}

/*
8 1 4 6 7 3 5 2

-2 -1 1 5 7 8 9
*/