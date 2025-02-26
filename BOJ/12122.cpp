#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

int N;
ld F;
string s;
int sm[500001];
const ld EPS = 1e-12;

void solve() {
	cin >> N >> F;
	cin >> s;
	for (int i = 1; i <= N; ++i) sm[i] = sm[i - 1] + (s[i - 1] == '1');
	vector<pair<ld, int> > v;
	for (int i = 0; i <= N; ++i) {
		if (i == 0) v.push_back(make_pair(0.0, 0));
		else v.push_back(make_pair((ld) sm[i] - i * F, i));
	}
	sort(v.begin(), v.end());
	ld dif = 1.0;
	int ans = N + 1;
	for (int i = 0; i + 1 < v.size(); ++i) {
		int a = min(v[i].second, v[i + 1].second), b = max(v[i].second, v[i + 1].second);
		int q = sm[b] - sm[a], p = b - a;
		ld ndif = abs((ld) q / p - F);
		if (abs(ndif - dif) < EPS) ans = min(ans, a);
		else if (ndif < dif) {
			dif = ndif;
			ans = a;
		}
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	for (int i = 1; i <= t; ++i) {
		cout << "Case #" << i << ": ";
		solve();
		cout << '\n';
	}
}