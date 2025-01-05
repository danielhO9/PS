#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, k;
ll a[100000];

void solve() {
	cin >> n >> k;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	map<ll, ll> m;
	for (int i = 0; i < n; ++i)
		++m[a[i]];
	deque<ll> q;
	for (auto [i, j] : m) {
		q.push_back(j);
	}
	sort(q.begin(), q.end());
	// for (auto i: q) cout << i << ' ';
	// cout << '\n';
	ll cur = 0;
	while (q.size() >= 2 && q.front() + cur <= k) {
		cur += q.front();
		q.back() += q.front();
		q.pop_front();
	}
	cout << q.size() << '\n';
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	while (t--)
		solve();
}