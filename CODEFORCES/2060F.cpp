#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

random_device rd;
mt19937_64 gen(rd());

const vector<vector<ll>> a = {
	{2, 7, 61},
	{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}
};

ll pow(ll a, ll b, ll MOD) {
	a %= MOD;
	if (b == 0) return 1;
	ll half = pow(a, b / 2, MOD);
	half = (half * half) % MOD;
	if (b % 2 == 0) return half;
	else return (half * a) % MOD;
}

bool millerRabin(ll n) {
	// int -> type 0
	// ll -> type 1
	int type = 0;
	if (type == 1 && n < 40) {
		for (auto i: a[type]) if (i == n) return true;
		return false;
	}
	for (int i = 0; i < a[type].size(); ++i) {
		if (a[type][i] == n) return true;
		ll k = n - 1;
		while (true) {
			ll temp = pow(a[type][i], k, n);
			if (temp == n - 1) break;
			if (k % 2 == 1) {
				if (temp == 1) break;
				else return false;
			}
			k /= 2;
		}
	}
	return true;
}

ll gcd(ll a, ll b) {
	if (a < b) swap(a, b);
	ll remainder;
	while (b != 0) {
		remainder = a % b;
		a = b;
		b = remainder;
	}
	return a;
}

ll f(ll x, ll c, ll MOD) { return (x * x + c) % MOD; }

void pollardRho(ll n, vector<ll>& ret) {
	// cout << (ll) n << '\n';
	if (n == 1) return;
	if (n % 2 == 0) {
		ret.push_back(2);
		pollardRho(n / 2, ret);
		return;
	}
	if (millerRabin(n)) {
		ret.push_back(n);
		return;
	}
	ll a, b, c, g = n;
	do {
		if (g == n) {
			uniform_int_distribution<> dist1(2, n - 1);
			a = dist1(gen); b = a;
			uniform_int_distribution<> dist2(1, 20);
			c = dist2(gen);
		}
		a = f(a, c, n);
		b = f(f(b, c, n), c, n);
		g = gcd(a > b ? a - b : b - a, n);
	} while (g == 1);
	pollardRho(g, ret);
	pollardRho(n / g, ret);
}

vector<ll> factorization(ll n) {
	vector<ll> ret;
	pollardRho(n, ret);
	sort(ret.begin(), ret.end());
	return ret;
}

const ll MOD = 998244353;

ll pow(ll a, ll b) {
	if (b == 0) return 1;
	ll half = pow(a, b / 2);
	half = (half * half) % MOD;
	if (b % 2) return (half * a) % MOD;
	else return half;
}

unordered_map<ll, ll> mi;
ll inv(ll a) {
	if (mi.find(a) != mi.end()) return mi[a];
	mi[a] = pow(a, MOD - 2);
	return mi[a];
}

ll comb(ll a, ll b) {
	ll ret = 1;
	for (ll i = a; i >= a - (b - 1); --i) {
		ret *= i;
		ret %= MOD;
	}
	for (ll i = 2; i <= b; ++i) {
		ret *= inv(i);
		ret %= MOD;
	}
	return ret;
}

ll k, n;

void solve() {
	cin >> k >> n;
	for (ll x = 1; x <= k; ++x) {
		if (x == 1) {
			cout << n << ' ';
			continue;
		}
		ll tmp = 1;
		vector<ll> facts = factorization(x);
		for (auto i: facts) tmp *= i;
		assert(tmp== x);
		vector< pair<ll, ll> > v;
		for (auto i: facts) {
			if (v.empty() || v.back().first != i) v.push_back(make_pair(i, 1));
			else ++v.back().second;
		}
		// for (auto i: v) cout << i.first << ' ' << i.second << '\n';
		// cout << '\n';
		vector<ll> cnt(min((ll) facts.size(), n) + 1);
		for (ll i = 1; i <= min((ll) facts.size(), n); ++i) {
			ll val = 1;
			for (auto& j: v) {
				val *= comb(i + j.second - 1, j.second);
				val %= MOD;
			}
			cnt[i] = val;
			for (ll j = 1; j < i; ++j) {
				cnt[i] += MOD;
				cnt[i] -= (cnt[j] * comb(i, j)) % MOD;
				cnt[i] %= MOD;
			}
		}
		// cout << '\n';
		// for (auto i: cnt) cout << i << ' ';
		// cout << '\n';
		ll ans = 0;
		for (ll i = 1; i <= min((ll) facts.size(), n); ++i) {
			ans += (comb(n + 1, i + 1) * cnt[i]) % MOD;
			ans %= MOD;
		}
		cout << ans << " ";

	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// init();
	int t; cin >> t;
	while (t--) solve();
}

/*
1
45 2

ans: 7
*/