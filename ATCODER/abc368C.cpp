#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll att[3] = {1, 1, 3};

void solve() {
	ll N; cin >> N;
	ll H[N]; for (int i = 0; i < N; ++i) cin >> H[i];
	int now = 0;

	ll ans = 0;
	for (int i = 0; i < N; ++i) {
		ll tmp = H[i] / 5;
		H[i] -= tmp * 5;
		ans += tmp * 3;
		while (H[i] > 0) {
			H[i] -= att[now];
			++ans;
			now += 1; now %= 3;
		}
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}