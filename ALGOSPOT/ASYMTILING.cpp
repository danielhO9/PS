#include <bits/stdc++.h>
using namespace std;

int cache1[101], cache2[101], MOD = 1000000007;
int n;

int matchCache1(int i) {
	if (i == 0) return 0;
	if (i == 1) return 1;
	if (i == 2) return 2;
	int& ret = cache1[i];
	if (ret != -1) return ret;
	ret = matchCache1(i - 1) + matchCache1(i - 2);
	ret %= MOD;
	return ret;
}

int matchCache2(int i) {
	if (i <= 2) return 0;
	int& ret = cache2[i];
	if (ret != -1) return ret;
	ret = 0;
	ret += matchCache2(i - 2); ret %= MOD;
	ret += matchCache2(i - 4); ret %= MOD;
	ret += matchCache1(i - 3); ret %= MOD;
	ret += matchCache1(i - 3); ret %= MOD;
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	memset(cache1, -1, sizeof(cache1));
	memset(cache2, -1, sizeof(cache2));
	int C; cin >> C;
	for (int i = 0; i < C; ++i) {
		cin >> n;
		cout << matchCache2(n) << "\n";
	}
}