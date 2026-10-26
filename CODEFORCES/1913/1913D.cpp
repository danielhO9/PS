#include <bits/stdc++.h>
using namespace std;

int MOD = 998244353, n;
int p[300000];

int normalize(long long x) {
	x %= MOD;
	if (x < 0) x += MOD;
	return x;
}

void solution() {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> p[i];
	int dpSum[n + 2], nxt, nxtSum[n];
	dpSum[n + 1] = 0; dpSum[n] = 1;
	for (int i = 0; i < n; ++i) nxtSum[i] = 0;
	stack<int> S;
	for (int i = n - 1; i >= 0; --i) {
		while (!S.empty() && p[S.top()] > p[i]) S.pop();
		nxt = S.empty() ? n : S.top();
		S.push(i);

		int dp = normalize(dpSum[i + 1] - dpSum[nxt + 1]);
		if (nxt != n) {
			dp = normalize(dp + nxtSum[nxt]);
			nxtSum[i] = normalize(dpSum[nxt] - dpSum[nxt + 1] + nxtSum[nxt]);
		}
		dpSum[i] = normalize(dp + dpSum[i + 1]);
	}

	int ret = 0;
	int mn = p[0];
	for (int i = 0; i < n; ++i) {
		mn = min(mn, p[i]);
		if (p[i] == mn) ret = normalize(ret + dpSum[i] - dpSum[i + 1]);
	}
	cout << ret << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solution();
}

/*
1
3
3 2 1
*/