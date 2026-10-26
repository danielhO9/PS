#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	int n, m, k; cin >> n >> m >> k;
	int sum[n + 1]; memset(sum, 0, sizeof(sum));
	vector<int> added[n + 1], deleted[n + 1];
	int l[m], r[m];
	for (int i = 0; i < m; ++i) {
		int a, b; cin >> a >> b;
		++sum[a]; added[a].push_back(i);
		if (b < n) { --sum[b + 1]; deleted[b + 1].push_back(i); }
		l[i] = a; r[i] = b;
	}
	int ocnt[n + 1]; memset(ocnt, 0, sizeof(ocnt));
	int tcnt[n + 1]; memset(tcnt, 0, sizeof(tcnt));
	int A = 0; int v = 0;
	vector<int> index[n + 1];
	set<int> S;
	for (int i = 1; i <= n; ++i) {
		for (auto j: deleted[i]) S.erase(j);
		for (auto j: added[i]) S.insert(j);
		v += sum[i];
		ocnt[i] = ocnt[i - 1];
		tcnt[i] = tcnt[i - 1];
		if (v == 0) ++A;
		if (v == 1) ++ocnt[i];
		if (v == 2) {
			++tcnt[i];
			for (auto j: S) index[i].push_back(j);
		}
	}
	vector<int> temp;
	for (int i = 0; i < m; ++i) temp.push_back(ocnt[r[i]] - ocnt[l[i] - 1]);
	sort(temp.begin(), temp.end()); reverse(temp.begin(), temp.end());
	int B = temp[0] + temp[1];
	for (int i = 1; i <= n; ++i) {
		if (index[i].empty()) continue;
		int a = index[i][0], b = index[i][1];
		int Ba = 0;
		Ba += ocnt[r[a]] - ocnt[l[a] - 1];
		Ba += ocnt[r[b]] - ocnt[l[b] - 1];
		int mini = max(l[a], l[b]);
		int maxi = min(r[a], r[b]);
		Ba += tcnt[maxi] - tcnt[mini - 1];
		B = max(B, Ba);
	}
	cout << A + B << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}