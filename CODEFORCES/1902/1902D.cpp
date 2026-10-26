#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL n, q;
string s;
LL x, y, l, r;
LL p[200001];
unordered_map<LL, vector<LL>> dic;

bool comp(const pair<int, int> &a,const pair<int, int> &b) {
	return a.first < b.first;
}

string solution() {
	cin >> x >> y >> l >> r;
	--l; --r;
	if (!dic[(x + n) * (2 * n + 1) + y + n].empty() && (dic[(x + n) * (2 * n + 1) + y + n].front() <= l || dic[(x + n) * (2 * n + 1) + y + n].back() > r)) return "YES";
	LL difx = -(p[r + 1] / (2 * n + 1) - n) + x;
	LL dify = -(p[r + 1] % (2 * n + 1) - n) + y;
	difx *= -1; dify *= -1;
	difx += p[l] / (2 * n + 1) - n;
	dify += p[l] % (2 * n + 1) - n;
	if (dic[(difx + n) * (2 * n + 1) + dify + n].empty()) return "NO";
	auto lo_it = lower_bound(dic[(difx + n) * (2 * n + 1) + dify + n].begin(), dic[(difx + n) * (2 * n + 1) + dify + n].end(), l + 1) - dic[(difx + n) * (2 * n + 1) + dify + n].begin();
	if (lo_it >= dic[(difx + n) * (2 * n + 1) + dify + n].size()) return "NO";
	if (dic[(difx + n) * (2 * n + 1) + dify + n][lo_it] <= r) return "YES";
	return "NO";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> q;
	cin >> s;
	LL tempx = 0, tempy = 0;
	for (int i = 0; i <= n; ++i) {
		p[i] = (tempx + n) * (2 * n + 1) + tempy + n;
		dic[(tempx + n) * (2 * n + 1) + tempy + n].push_back(i);
		if (i == n) break;
		if (s[i] == 'U') ++tempy;
		if (s[i] == 'D') --tempy;
		if (s[i] == 'L') --tempx;
		if (s[i] == 'R') ++tempx;
	}
	while (q--) cout << solution() << '\n';
}

/*
10 1
DLUDLRULLD
-1 0 3 9
*/