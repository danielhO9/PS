#include <bits/stdc++.h>
using namespace std;

int N, K;
int a[100];
int cache[100001];

int matchCache(int n) {
	if (n == 0) return 0;
	int& ret = cache[n];
	if (ret != -1) return ret;
	ret = 0;
	for (int i = 0; i < N; ++i) if (n >= a[i]) {
		if (matchCache(n - a[i]) == 0) {
			ret = 1;
			break;
		}
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> K; for (int i = 0; i < N; ++i) cin >> a[i];
	memset(cache, -1, sizeof(cache));
	if (matchCache(K)) cout << "First";
	else cout << "Second";
}