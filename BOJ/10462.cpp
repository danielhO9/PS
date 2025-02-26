#include <bits/stdc++.h>
using namespace std;
const int MAX = 987654321;

int cache[6001];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int c, r;
	vector<pair<int, int>> v;
	while (cin >> c >> r) {
		v.push_back(make_pair(c, r));
	}
	sort(v.begin(), v.end(), [] (const pair<int, int>& a, const pair<int, int>& b) {
		return a.second < b.second;
	});
	for (int i = 1; i <= v.size(); ++i) cache[i] = MAX;
	int ncache[6001];
	for (int i = 0; i < v.size(); ++i) {
		memcpy(ncache, cache, sizeof(int) * (v.size() + 1));
		for (int j = 0; j < v.size(); ++j) if (cache[j] + v[i].first <= v[i].second) {
			ncache[j + 1] = min(ncache[j + 1], cache[j] + v[i].first);
		}
		for (int j = (int) v.size() - 1; j >= 0; --j) ncache[j] = min(ncache[j], ncache[j + 1]);
		swap(cache, ncache);
	}
	for (int i = v.size(); i >= 0; --i) if (cache[i] != MAX) {
		cout << i;
		return 0;
	}
}