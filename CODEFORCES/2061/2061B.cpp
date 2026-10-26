#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

ll n;

void solve() {
	cin >> n;
	vector<ll> a(n);
	for (int i = 0; i < n; ++i) cin >> a[i];
	unordered_map<ll, int, custom_hash> m;
	ll mx = -1;
	multiset<ll> s;
	for (int i = 0; i < n; ++i) s.insert(a[i]);
	for (int i = 0; i < n; ++i) {
		if (m.find(a[i]) != m.end()) {
			mx = max(mx, a[i]);
			++m[a[i]];
		} else m[a[i]] = 1;
	}
	if (mx == -1) {
		cout << -1 << '\n';
		return;
	}
	s.erase(s.find(mx));
	s.erase(s.find(mx));
	a.clear();
	for (auto i: s) a.push_back(i);

	sort(a.begin(), a.end());
	for (int i = 0; i + 1 < a.size(); ++i) {
		if (a[i + 1] - a[i] < 2 * mx) {
			cout << mx << ' ' << mx << ' ' << a[i + 1] << ' ' << a[i] << '\n';
			return;
		}
	}
	cout << -1 << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}