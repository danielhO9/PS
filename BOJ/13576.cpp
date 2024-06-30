#include <bits/stdc++.h>
using namespace std;

// S[i...], S의 lcp 길이
vector<int> getZ(const string &s) {
	const int n = s.size();
	int l = 0, r = 0;
	vector<int> z(n, 0);
	z[0] = n;
	for (int i = 1; i < n; ++i) {
		if (i <= r)
			z[i] = min(r - i, z[i - l]);
		while (s[i + z[i]] == s[z[i]])
			++z[i];
		if (i > r)
			l = i;
		r = max(r, i + z[i] - 1);
	}
	return z;
}

void solve() {
	string S; cin >> S;
	int n = S.size();
	vector<int> z = getZ(S);
	auto tmp = z;
	sort(tmp.begin(), tmp.end());
	int acnt = 0;
	vector<pair<int, int>> ans;
	for (int i = n - 1; i >= 0; --i) {
		if (z[i] == n - i) {
			++acnt;
			ans.push_back({n - i, tmp.end() - lower_bound(tmp.begin(), tmp.end(), n - i)});
		}
	}
	cout << acnt << '\n';
	for (auto i : ans)
		cout << i.first << ' ' << i.second << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}