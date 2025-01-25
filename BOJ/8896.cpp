#include <bits/stdc++.h>
using namespace std;

int N;

void solve() {
	cin >> N;
	vector<string> rsp(N);
	for (int i = 0; i < N; ++i) cin >> rsp[i];
	int k = rsp[0].size();
	bool rem[N]; for (int i = 0; i < N; ++i) rem[i] = true;
	for (int i = 0; i < k; ++i) {
		vector<int> r, s, p;
		for (int j = 0; j < N; ++j) if (rem[j]) {
			if (rsp[j][i] == 'R') r.push_back(j);
			if (rsp[j][i] == 'S') s.push_back(j);
			if (rsp[j][i] == 'P') p.push_back(j);
		}
		if (r.size() > 0 && s.size() > 0 && p.size() > 0) continue;
		if (r.size() > 0 && s.size() > 0) for (int j: s) rem[j] = false;
		if (p.size() > 0 && s.size() > 0) for (int j: p) rem[j] = false;
		if (r.size() > 0 && p.size() > 0) for (int j: r) rem[j] = false;
	}
	vector<int> ans;
	for (int i = 0; i < N; ++i) if (rem[i]) ans.push_back(i);
	if (ans.size() >= 2) cout << 0 << '\n';
	else cout << ans[0] + 1 << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}