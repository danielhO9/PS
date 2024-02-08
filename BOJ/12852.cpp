#include <bits/stdc++.h>
using namespace std;

int N, cache[1000001], choice[1000001];

int matchCache(int n) {
	if (n == 1) return 0;
	int& ret = cache[n];
	if (ret != -1) return ret;
	ret = INT32_MAX;
	if (n % 3 == 0 && ret > matchCache(n / 3) + 1) {
		ret = matchCache(n / 3) + 1;
		choice[n] = n / 3;
	}
	if (n % 2 == 0 && ret > matchCache(n / 2) + 1) {
		ret = matchCache(n / 2) + 1;
		choice[n] = n / 2;
	}
	if (ret > matchCache(n - 1) + 1) {
		ret = matchCache(n - 1) + 1;
		choice[n] = n - 1;
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	memset(cache, -1, sizeof(cache));
	cin >> N;
	cout << matchCache(N) << "\n";
	while (N) {
		cout << N << " ";
		N = choice[N];
	}
}