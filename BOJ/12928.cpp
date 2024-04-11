#include <bits/stdc++.h>
using namespace std;

int cache[51][1001];

int combTwo(int n) { return n * (n - 1) / 2; }

int matchCache(int n, int s) {
	if (n <= 2) return s ? 0 : 1;
	int& ret = cache[n][s];
	if (ret != -1) return ret;
	ret = 0;
	for (int i = 1; i <= n - 2; ++i) {
		if (combTwo(i + 1) <= s && matchCache(n - i, s - combTwo(i + 1))) {
			ret = 1;
			break;
		}
	}
	return ret;
}

void solve() {
	int N, S; cin >> N >> S;
	memset(cache, -1, sizeof(cache));
	cout << matchCache(N, S);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}