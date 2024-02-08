#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int N;
LL s[300000], times[300000], MOD = 1000000007, ans;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> s[i];
	sort(s, s + N);
	times[0] = 1;
	for (int i = 1; i < 300000; ++i) {
		times[i] = times[i - 1] * 2;
		times[i] %= MOD;
	}
	for (int i = 0; i < N; ++i) {
		ans += times[i] * s[i]; ans %= MOD;
		ans -= times[N - 1 - i] * s[i];
		ans += ((times[N - 1 - i] * s[i]) / MOD + 1) * MOD;
		ans %= MOD;
	}
	cout << ans;
}