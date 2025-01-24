#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
int w[1000], s[1000];
ll v[1000];
ll cache[20001];
int idx[1000];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> w[i] >> s[i] >> v[i];
	for (int i = 0; i < N; ++i) idx[i] = i;
	sort(idx, idx + N, [](int a, int b) {
		return s[a] + w[a] < s[b] + w[b];
	});
	for (int i = 0; i < N; ++i) {
		for (int j = 2e4 - w[idx[i]]; j >= 0; --j) if (j <= s[idx[i]]) {
			cache[w[idx[i]] + j] = max(cache[w[idx[i]] + j], cache[j] + v[idx[i]]);
		}
	}
	ll ans = 0;
	for (int i = 0; i <= 2e4; ++i) ans = max(ans, cache[i]);
	cout << ans;
}