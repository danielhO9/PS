#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, m;
ll a[300000];
ll b[300000];

void solve() {
	cin >> n >> m;
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < m; ++i) cin >> b[i];
	ll kevin = a[0];
	deque<ll> A;
	vector<ll> B;
	for (int i = 0; i < n; ++i) if (a[i] > kevin) A.push_back(a[i]);
	for (int i = 0; i < m; ++i) if (b[i] > kevin) B.push_back(b[i]);
	sort(A.begin(), A.end());
	sort(B.begin(), B.end());
	vector<ll> cnt(B.size());
	for (int i = 0; i < B.size(); ++i) {
		while (!A.empty() && B[i] > A.front()) A.pop_front();
		cnt[i] = A.size();
	}
	for (ll k = 1; k <= m; ++k) {
		ll ans = m / k;
		ll rem = m % k;
		for (int i = rem; i < B.size(); i += k) {
			ans += cnt[i];
		}
		cout << ans << ' ';
	}
	cout << '\n';

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}