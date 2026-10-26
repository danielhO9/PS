#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;

int n;
int a[200000];
ll cache[200001];

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i <= n; ++i) cache[i] = 0;
	pair<ll, ll> t, f;
	if (a[0] == 0) {
		t = {0, 1};
		f = {1, 1};
	} else {
		t = {-1, 0};
		f = {1, 1};
	}
	for (int i = 1; i < n; ++i) {
		pair<ll, ll> nf, nt;
		if (t.first == a[i] || f.first == a[i]) {
			nt = {a[i], 0};
			if (t.first == a[i]) {
				nt.second += t.second;
				nt.second %= MOD;
			}
			if (f.first == a[i]) {
				nt.second += f.second;
				nt.second %= MOD;
			}
		} else nt = {-1, 0};
		nf = {t.first + 1, t.second};
		t = nt, f = nf;
	}
	cout << (t.second + f.second) % MOD << '\n';

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}