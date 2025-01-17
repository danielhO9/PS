#include <bits/stdc++.h>
using namespace std;

// 0-based
vector<vector<int>> PCD(vector<int> v) {
	vector<bool> vis(v.size(), false);
	vector<vector<int>> ret;
	for (int i = 0; i < v.size(); ++i) if (!vis[i]) {
		ret.push_back({});
		int j = i;
		while (!vis[j]) {
			ret.back().push_back(j);
			vis[j] = true;
			j = v[j];
		}
	}
	return ret;
}