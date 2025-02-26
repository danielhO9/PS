#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007;

ll cache[100000];
ll sm[100000];

string s;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> s;
	cache[0] = 1; sm[0] = 1;
	for (int i = 1; i < 100000; ++i) {
		cache[i] = sm[i - 1] + 1;
		cache[i] %= MOD;
		sm[i] = sm[i - 1] + cache[i];
		sm[i] %= MOD;
	}
	ll ans = 0;
	for (int i = 0; i < s.size(); ++i) if (s[i] == 'O') {
		ans += cache[i];
		ans %= MOD;
	}
	cout << ans;
}