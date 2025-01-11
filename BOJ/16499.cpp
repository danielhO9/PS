#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	map<vector<int>, bool> m;
	int N; cin >> N;
	while (N--) {
		string s; cin >> s;
		vector<int> cnt(26);
		for (auto i: s) ++cnt[i - 'a'];
		m[cnt] = true;
	}
	cout << m.size();
}