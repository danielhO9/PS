#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, m;
ll l[200000];
vector<ll> a[200000];
ll cond[200000];
ll res[200000];
bool used[200010];
const int MAX = 200010;
ll val[MAX];

void solve() {
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		cin >> l[i];
		a[i].clear();
		for (int j = 0; j < l[i]; ++j) {
			ll tmp; cin >> tmp;
			a[i].push_back(tmp);
		}
	}
	for (int i = 0; i < n; ++i) {
		vector<ll> tmp;
		for (auto j: a[i]) if (j < MAX) {
			tmp.push_back(j);
			used[j] = true;
		}
		bool flag = false;
		for (int j = 0; j < MAX; ++j) {
			if (!used[j]) {
				if (!flag) {
					cond[i] = j;
					flag = true;
				} else {
					res[i] = j;
					break;
				}
			}
		}
		for (auto i: tmp) used[i] = false;
	}
	ll maxres = 0ll;
	for (int i = 0; i < n; ++i) maxres = max(maxres, res[i]);
	ll ans = 0ll;
	if (maxres < m) {
		ans = maxres * (maxres + 1) - (maxres * (maxres + 1) / 2) + (m * (m + 1) / 2);
	} else {
		ans = maxres * (m + 1);
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}