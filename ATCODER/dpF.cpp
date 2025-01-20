#include <bits/stdc++.h>
using namespace std;

string s, t;
int cache[3000][3000];
pair<int, int> prv[3000][3000];

int matchCache(int i, int j) {
	if (i == 0 && j == 0) {
		prv[i][j] = {i, j};
		return (s[i] == t[j]);
	}
	int& ret = cache[i][j];
	if (ret != -1) return ret;
	prv[i][j] = {i, j};
	if (j >= 1 && ret < matchCache(i, j - 1)) {
		ret = matchCache(i, j - 1);
		prv[i][j] = {i, j - 1};
	}
	if (i >= 1 && ret < matchCache(i - 1, j)) {
		ret = matchCache(i - 1, j);
		prv[i][j] = {i - 1, j};
	}
	if (s[i] == t[j]) {
		if (i >= 1 && j >= 1 && ret < matchCache(i - 1, j - 1) + 1) {
			ret = matchCache(i - 1, j - 1) + 1;
			prv[i][j] = {i - 1, j - 1};
		}
		ret = max(ret, 1);
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> s >> t;
	memset(cache, -1, sizeof(cache));
	matchCache((int) s.size() - 1, (int) t.size() - 1);
	int i = (int) s.size() - 1, j = (int) t.size() - 1;
	string ans;
	while (true) {
		// cout << i << ' ' << j << '\n';
		auto pidx = prv[i][j];
		if (pidx.first == i && pidx.second == j) {
			if (s[i] == t[j]) ans += s[i];
			break;
		}
		if (matchCache(pidx.first, pidx.second) != matchCache(i, j)) {
			ans += s[i];
		}
		i = pidx.first;
		j = pidx.second;
	}
	reverse(ans.begin(), ans.end());
	cout << ans;
}