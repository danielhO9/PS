#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

unordered_map<LL, pair<LL, char>> M;

void solve() {
	LL s, t; cin >> s >> t;
	if (s == t) {
		cout << 0;
		return;
	}
	queue<LL> Q; Q.push(s); M[s] = {-1, ' '};
	while (!Q.empty()) {
		LL here = Q.front(); Q.pop();
		LL there;
		there = here * here;
		if (there <= t && M.find(there) == M.end()) {
			M[there] = {here, '*'};
			Q.push(there);
		}
		there = here * 2;
		if (there <= t && M.find(there) == M.end()) {
			M[there] = {here, '+'};
			Q.push(there);
		}
		there = 1;
		if (there <= t && M.find(there) == M.end()) {
			M[there] = {here, '/'};
			Q.push(there);
		}
		if (M.find(t) != M.end()) break;
	}
	vector<char> ans;
	if (M.find(t) == M.end()) {
		cout << -1;
		return;
	}
	while (t != s) {
		ans.push_back(M[t].second);
		t = M[t].first;
	}
	reverse(ans.begin(), ans.end());
	for (auto i: ans) cout << i;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}