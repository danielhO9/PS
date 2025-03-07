#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1e9;
string s;
ll cache[300][300];

ll matchCache(int l, int r) {
	if (l == r) return 1;
	if (s[l] != s[r]) return 0;
	ll& ret = cache[l][r];
	if (ret != -1) return ret;
	vector<int> v;
	for (int i = l + 1; i <= r; ++i) if (s[l] == s[i]) v.push_back(i);
	ret = 0;
	for (auto i: v) {
		ret += (matchCache(l + 1, i - 1) * matchCache(i, r)) % MOD;
		ret %= MOD;
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> s;
	memset(cache, -1, sizeof(cache));
	cout << matchCache(0, (int) s.size() - 1);
}