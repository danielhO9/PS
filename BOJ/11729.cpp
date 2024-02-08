#include <bits/stdc++.h>
using namespace std;

void solve(int n, int s, int e) {
	if (n == 1) {
		cout << s << ' ' << e << '\n';
		return;
	}
	solve(n - 1, s, 6 - s - e);
	cout << s << ' ' << e << '\n';
	solve(n - 1, 6 - s - e, e);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int N; cin >> N;
	int ans = 1;
	for (int i = 0; i < N - 1; ++i) {
		ans *= 2; ++ans;
	}
	cout << ans << '\n';
	solve(N, 1, 3);
}