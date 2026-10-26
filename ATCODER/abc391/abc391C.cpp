#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, Q;
int cor[1000001];
int cnt[1000001];

void solve() {
	cin >> N >> Q;
	for (int i = 1; i <= N; ++i) cor[i] = i;
	for (int i = 1; i <= N; ++i) cnt[i] = 1;
	int ans = 0;
	while (Q--) {
		int t; cin >> t;
		if (t == 1) {
			int P, H; cin >> P >> H;
			if (cnt[cor[P]] == 2) --ans;
			--cnt[cor[P]];
			cor[P] = H;
			if (cnt[cor[P]] == 1) ++ans;
			++cnt[cor[P]];
		} else cout << ans << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}