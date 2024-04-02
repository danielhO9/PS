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
	int N, K; cin >> N >> K;
	string S; cin >> S;
	if (N <= K) {
		cout << min((N + K) / 2, N);
		return;
	}
	vector<int> z = getZ(S);
	for (int i = min(N - 1, (N + K) / 2); i > 0; --i) if (z[i] == N - i) {
		if ((N + i - 1) / i * i - N <= K) {
			cout << i;
			return;
		}
	}
	cout << 0;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}