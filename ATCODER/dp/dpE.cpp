#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAX = 1e9 + 1;

ll N, W;
ll w[100], v[100];
ll cache[100001];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> W;
	for (int i = 0; i < N; ++i) cin >> w[i] >> v[i];
	for (int i = 0; i <= 100000; ++i) cache[i] = MAX;
	cache[0] = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 100000; j >= 0; --j) {
			if (j >= v[i]) cache[j] = min(cache[j], cache[j - v[i]] + w[i]);
			else cache[j] = min(cache[j], w[i]);
		}
	}
	for (int i = 100000; i >= 0; --i) if (cache[i] <= W) {
		cout << i;
		return 0;
	}
}