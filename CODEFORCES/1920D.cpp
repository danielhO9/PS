#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	LL n, q; cin >> n >> q;
	LL l = 0;
	unordered_map<LL, LL> M;
	vector<LL> lh;
	while (n--) {
		LL b, x; cin >> b >> x;
		if (l >= 1e18 + 5) continue;
		if (b == 1) M[l++] = x;
		else {
			lh.push_back(l);
			if (l <= (LL) floor((double)(1e18 + 5) / (x + 1))) l *= (x + 1);
			else l = 1e18 + 5;
		}
	}
	vector<LL> Q(q); for (int i = 0; i < q; ++i) { cin >> Q[i]; --Q[i]; }
	for (int i = 0; i < q; ++i) {
		LL t = Q[i]; LL index = lh.size(); --index;
		while (M.find(t) == M.end()) {
			t %= lh[index]; --index;
		}
		cout << M[t] << ' ';
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}