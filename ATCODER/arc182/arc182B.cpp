#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, K;

void solve() {
	cin >> N >> K;
	ll num = (1 << (K - 1));
	ll odd = 1ll;
	for (int i = 0; i < N; ++i) {
		cout << num * odd << ' ';
		if (odd + 2 >= (1ll << K)) continue;
		odd += 2;
		while (num * odd >= (1ll << K)) {
			num /= 2ll;
		}
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}