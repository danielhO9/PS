#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n, m; cin >> n >> m;
	int a[n + 1], b[m + 1];
	int aind[n + 1], bind[m + 1];
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		aind[a[i]] = i;
	}
	for (int i = 1; i <= m; ++i) {
		cin >> b[i];
		bind[b[i]] = i;
	}
	vector<int> aans, bans;
	for (int i = 1; i <= n; ++i) {
		if (a[i] == i) continue;
		int j = aind[i];
		aans.push_back(i);
		aans.push_back(j - i);
		aans.push_back(n - j + 1);
		a[j] = a[i]; a[i] = i;
		aind[a[j]] = j; aind[i] = i;
	}
	for (int i = 1; i <= m; ++i) {
		if (b[i] == i) continue;
		int j = bind[i];
		bans.push_back(i);
		bans.push_back(j - i);
		bans.push_back(m - j + 1);
		b[j] = b[i]; b[i] = i;
		bind[b[j]] = j; bind[i] = i;
	}
	if (aans.size() % 2 != bans.size() % 2) {
		if (n % 2 == 1) {
			for (int i = 1; i <= n; ++i) aans.push_back(1);
		} else if (m % 2 == 1) {
			for (int i = 1; i <= m; ++i) bans.push_back(1);
		} else {
			cout << -1 << '\n';
			return;
		}
	}
	if (aans.size() % 2 == bans.size() % 2) {
		if (aans.size() > bans.size()) {
			while (aans.size() != bans.size()) { bans.push_back(1); bans.push_back(m); }
		} else if (aans.size() < bans.size()) {
			while (aans.size() != bans.size()) { aans.push_back(1); aans.push_back(n); }
		}
	}
	cout << aans.size() << '\n';
	for (int i = 0; i < aans.size(); ++i) {
		cout << aans[i] << ' ' << bans[i] << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}