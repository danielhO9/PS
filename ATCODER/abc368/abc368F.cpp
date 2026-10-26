#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll grundy[100001];
bool prime[100001];

void init() {
	for (int i = 2; i <= 1e5; ++i) prime[i] = true;
	for (int i = 2; i <= 1e5; ++i) {
		if (!prime[i]) continue;
		for (int j = i * 2; j <= 1e5; j += i) prime[j] = false;
		// if (i <= 10) cout << i << ' ';
		ll tmp = i;
		while (tmp <= 1e5) {
			for (ll j = tmp; j <= 1e5; j += tmp) {
				// if (j <= 10) cout << j << ' ';
				++grundy[j];
			}
			tmp *= i;
		}
	}
	// for (int i = 1; i <= 10; ++i) cout << grundy[i] << ' ';
}

void solve() {
	int N; cin >> N;
	ll ans = 0;
	for (int i = 0; i < N; ++i) {
		ll A; cin >> A;
		ans ^= grundy[A];
	}
	if (ans == 0) cout << "Bruno";
	else cout << "Anna";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	init();
	solve();
}