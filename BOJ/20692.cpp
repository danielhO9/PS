#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;

// 0-based
vector<vector<int>> PCD(vector<int> v) {
	vector<bool> vis(v.size(), false);
	vector<vector<int>> ret;
	for (int i = 0; i < v.size(); ++i) if (!vis[i]) {
		ret.push_back({});
		int j = i;
		while (!vis[j]) {
			ret.back().push_back(j);
			vis[j] = true;
			j = v[j];
		}
	}
	return ret;
}

int N;

pair<ll, ll> f(int x) {
	int cnt = 0;
	while (x % 2 == 0) {
		++cnt;
		x /= 2;
	}
	vector<bool> vis(x, false);
	int cur = 1 % x;
	int ans = 0;
	while (!vis[cur]) {
		++ans;
		vis[cur] = true;
		cur *= 2;
		cur %= x;
	}
	return {cnt, ans};
}

ll gcd(ll a, ll b) {
	if (a < b) swap(a, b);
	if (b == 0) return a;
	return gcd(b, a % b);
}

ll gcd(vector<ll>& v, ll a) {
	ll val = 0;
	ll p = 1;
	for (int i = 0; i < v.size(); ++i) {
		val += (p % a) * (v[i] % a);
		val %= a;
		p *= MOD;
		p %= a;
	}
	return gcd(a, val);
}

void solve() {
	cin >> N;
	vector<int> v(N);
	for (int i = 0; i < N; ++i) cin >> v[i];
	for (int i = 0; i < N; ++i) --v[i];
	auto pcd = PCD(v);
	// pcd = {};
	// vector<int> tmp; for (int i = 0; i < 100000; ++i) tmp.push_back(0);
	// pcd.push_back(tmp);
	vector<ll> lcd = {1};
	ll mx = 0;
	for (auto i: pcd) {
		auto tmp = f(i.size());
		mx = max(mx, tmp.first);

		if (tmp.second == 1) continue;
		ll g = gcd(lcd, tmp.second);
		ll t = tmp.second / g;
		for (auto& j: lcd) j *= t;
		lcd.push_back(0);
		for (int j = 0; j < lcd.size(); ++j) {
			if (lcd[j] >= MOD) {
				lcd[j + 1] += lcd[j] / MOD;
				lcd[j] %= MOD;
			}
		}
		if (lcd.back() == 0) lcd.pop_back();
	}
	cout << (mx + lcd[0]) % MOD;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}