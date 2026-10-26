#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N;
string S;
ll ocnt[500000];

void solve() {
	cin >> N >> S;
	ocnt[0] = (S[0] == '1');
	for (int i = 1; i < N; ++i) ocnt[i] = ocnt[i - 1] + (S[i] == '1');
	ll ans = 0;
	for (int i = 0; i < N; ++i) if (S[i] == '0') {
		ans += ocnt[N - 1] - ocnt[i];
	}
	for (int i = 0; i < N; ++i) if (S[i] == '0') {
		ll tmp = ans;
		tmp -= ocnt[N - 1] - ocnt[i];
		tmp += ocnt[i];
		ans = min(ans, tmp);
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}