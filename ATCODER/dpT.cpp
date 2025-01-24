#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

int N;
string s;
ll cache[3001];
ll ncache[3001];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> s;
	cache[1] = 1;
	for (int i = 0; i < N - 1; ++i) {
		if (s[i] == '<') {
			ncache[1] = 0;
			ll sum = cache[1];
			for (int j = 2; j <= i + 2; ++j) {
				ncache[j] = sum;
				sum += cache[j];
				sum %= MOD;
			}
		} else {
			ncache[i + 2] = 0;
			ll sum = 0;
			for (int j = i + 1; j >= 1; --j) {
				sum += cache[j];
				sum %= MOD;
				ncache[j] = sum;
			}
		}
		swap(ncache, cache);
	}
	ll ans = 0;
	for (int i = 1; i <= N; ++i) {
		ans += cache[i];
		ans %= MOD;
	}
	cout << ans;
}