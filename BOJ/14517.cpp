#include <bits/stdc++.h>
using namespace std;

int cache[1000][1000], MOD = 10007;

int matchCache(string& S, int s, int e) {
	if (s > e) return 0;
	if (s == e) return 1;
	int& ret = cache[s][e];
	if (ret != -1) return ret;
	ret = matchCache(S, s + 1, e) + matchCache(S, s, e - 1) - matchCache(S, s + 1, e - 1);
	if (S[s] == S[e]) ret += 1 + matchCache(S, s + 1, e - 1);
	ret += MOD * (ret / MOD + 1); ret %= MOD;
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	string S; cin >> S;
	memset(cache, -1, sizeof(cache));
	cout << matchCache(S, 0, S.size() - 1);
}