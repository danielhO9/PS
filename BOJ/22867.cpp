#include <bits/stdc++.h>
using namespace std;

int N;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	vector<pair<string, int>> v;
	cin >> N;
	for (int i = 0; i < N; ++i) {
		string s1, s2; cin >> s1 >> s2;
		v.push_back({s1, 1});
		v.push_back({s2, -1});
	}
	sort(v.begin(), v.end());
	int mx = 0, cur = 0;
	for (auto i: v) {
		cur += i.second;
		mx = max(mx, cur);
	}
	cout << mx;
}