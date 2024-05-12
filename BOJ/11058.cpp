#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll cache[101];

void solve() {
	memset(cache, -1, sizeof(cache));
	cache[1] = 1; cache[2] = 2;
	for (int i = 1; i <= 100; ++i) {
		ll tmp = cache[i];
		for (int j = i + 1; j <= 100; ++j) cache[j] = max(cache[j], ++tmp);
		tmp = cache[i];
		for (int j = i + 3; j <= 100; ++j) {
			tmp += cache[i];
			cache[j] = max(cache[j], tmp);
		}
	}
	int N; cin >> N;
	cout << cache[N];
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}