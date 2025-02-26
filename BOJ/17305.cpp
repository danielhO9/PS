#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, w;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> w;
	vector<ll> t, f;
	for (int i = 0; i < N; ++i) {
		ll a, b; cin >> a >> b;
		if (a == 3) t.push_back(b);
		else f.push_back(b);
	}
	sort(t.begin(), t.end()); reverse(t.begin(), t.end());
	sort(f.begin(), f.end()); reverse(f.begin(), f.end());
	vector<ll> smt(t.size() + 1), smf(f.size() + 1);
	for (int i = 0; i < t.size(); ++i) smt[i + 1] = smt[i] + t[i];
	for (int i = 0; i < f.size(); ++i) smf[i + 1] = smf[i] + f[i];
	ll ans = 0;
	for (int i = 0; i <= w / 5; ++i) {
		int j = (w - i * 5) / 3;
		// cout << i << ' ' << j << "\n";
		ans = max(ans, smf[min(i, (int) f.size())] + smt[min(j, (int) t.size())]);
	}
	cout << ans;
}