#include <bits/stdc++.h>
using namespace std;

// S[i...], S의 공통 접두사 길이
vector<int> getZ(const string& S) {
	const int n = S.size();
	int l = 0, r = 0;
	vector<int> z(n, 0);
	z[0] = n;
	for (int i = 1; i < n; ++i) {
		if (i <= r) z[i] = min(r - i, z[i - l]);
		while (S[i + z[i]] == S[z[i]]) ++z[i];
		if (i > r) l = i;
		r = max(r, i + z[i] - 1);
	}
	return z;
}

void solve() {
	string S; cin >> S;
	int n = S.size();
	reverse(S.begin(), S.end());
	vector<int> z = getZ(S);
	int M; cin >> M;
	while (M--) {
		int i; cin >> i;
		cout << z[n - i] << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}