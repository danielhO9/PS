#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string S;
int Q;

void solve() {
	ll dif = 'A' - 'a';
	cin >> S;
	cin >> Q;
	ll n = S.size();
	while (Q--) {
		ll K; cin >> K;
		--K;
		ll m = K / n;
		ll cnt = 0;
		for (ll i = 60; i >= 0; --i) {
			if (m >= (1ll << i)) {
				m -= (1ll << i);
				cnt ^= 1;
			}
		}
		if (cnt % 2) {
			if ('a' <= S[K % n] && S[K % n] <= 'z') cout << char(S[K % n] + dif) << ' ';
			else cout << char(S[K % n] - dif) << ' ';
		} else {
			cout << S[K % n] << ' ';
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}