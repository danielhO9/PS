#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAX = 987654321;

int N;
ll sound[2000];
ll cache[2000][2000];

ll matchCache(int a, int b) {
	if (a == b) return MAX;
	if (a > b) swap(a, b);
	if (a == -1) {
		ll ret = 0ll;
		for (int i = 0; i < b; ++i) ret += abs(sound[i] - sound[i + 1]);
		return ret;
	}
	ll& ret = cache[a][b];
	if (ret != -1) return ret;
	ret = MAX;
	if (a == b - 1) {
		for (int i = -1; i < b - 1; ++i) {
			ll tmp = 0ll;
			if (i != -1) tmp = abs(sound[i] - sound[b]);
			ret = min(ret, matchCache(a, i) + tmp);
		}
	} else ret = min(ret, matchCache(a, b - 1) + abs(sound[b] - sound[b - 1]));
	return ret;
}

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> sound[i];
	memset(cache, -1, sizeof(cache));
	ll ans = MAX;
	for (int i = -1; i < N; ++i) ans = min(ans, matchCache(i, N - 1));
	// for (int i = -1; i < N; ++i) {
	// 	for (int j = -1; j < N; ++j) cout << matchCache(i, j) << ' ';
	// 	cout << "\n";
	// }
	cout << ans;

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}