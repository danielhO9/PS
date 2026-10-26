#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL n;

bool check(vector<LL>& a, vector<LL>& sum, LL limit) {
	priority_queue<pair<LL, LL>, vector<pair<LL, LL>>, greater<pair<LL, LL>>> Q;
	Q.push({0LL, 0LL});
	vector<LL> cache(n + 1);
	for (LL i = 1; i <= n; ++i) {
		while (sum[i - 1] - Q.top().second > limit) Q.pop();
		cache[i] = Q.top().first + a[i];
		Q.push({cache[i], sum[i]});
	}
	LL ans = LLONG_MAX;
	for (LL i = n; i >= 1; --i) {
		if (sum[n] - sum[i] > limit) break;
		ans = min(ans, cache[i]);
	}
	if (ans <= limit) return true;
	return false;
}

void solve() {
	cin >> n;
	LL maxa = 0;
	vector<LL> a(n + 1), sum(n + 1);
	for (LL i = 1; i <= n; ++i) {
		cin >> a[i];
		maxa = max(maxa, a[i]);
		sum[i] = sum[i - 1] + a[i];
	}
	LL left = maxa, right = 1e14, mid;
	while (left < right) {
		mid = (left + right) / 2;
		// cout << left << ' ' << right << '\n';
		if (check(a, sum, mid)) right = mid;
		else left = mid + 1;
	}
	// cout << check(a, sum, 5);
	cout << left << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}