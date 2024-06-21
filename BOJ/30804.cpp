#include <bits/stdc++.h>
using namespace std;

void solve() {
	int N; cin >> N;
	vector<int> S(N); for (int i = 0; i < N; ++i) cin >> S[i];
	int l = 0, r = 0;
	int ans = 1;
	vector<int> cnt(10, 0);
	++cnt[S[0]];
	int tcnt = 1;
	while (r < N) {
		ans = max(ans, r - l + 1);
		++r; ++cnt[S[r]];
		if (cnt[S[r]] == 1) ++tcnt;
		while (tcnt > 2) {
			--cnt[S[l]];
			if (cnt[S[l]] == 0) --tcnt;
			++l;
		}
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}