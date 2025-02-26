#include <bits/stdc++.h>
using namespace std;

int N;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	vector<pair<string, string>> v;
	cin >> N;
	for (int i = 0; i < N; ++i) {
		string s1, s2; cin >> s1 >> s2;
		v.push_back({s1, s2});
	}
	sort(v.begin(), v.end(), [](const pair<string, string>& a, const pair<string, string>& b) {
		if (a.second == b.second) return a.first < b.first;
		return a.second < b.second;
	});
	unordered_map<string, int> m;
	for (int i = 0; i < N; ++i) m[v[i].first + v[i].second] = i;
	int Q; cin >> Q;
	while (Q--) {
		string s1, s2; cin >> s1 >> s2;
		int idx = m[s1 + s2];
		for (int i = idx / 3 * 3; i < (idx / 3 * 3) + 3; ++i) if (i != idx) {
			cout << v[i].first << ' ' << v[i].second << '\n';
		}
	}
}