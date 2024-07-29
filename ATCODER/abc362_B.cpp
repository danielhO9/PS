#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

pair<int, int> cor[3];

int dis(int i, int j) {
	return (cor[i].first - cor[j].first) * (cor[i].first - cor[j].first) + (cor[i].second - cor[j].second) * (cor[i].second - cor[j].second);
}


void solve() {
	for (int i = 0; i < 3; ++i) cin >> cor[i].first >> cor[i].second;
	vector<int> dist;
	dist.push_back(dis(0, 1));
	dist.push_back(dis(0, 2));
	dist.push_back(dis(2, 1));
	sort(dist.begin(), dist.end());
	if (dist[0] + dist[1] == dist[2]) cout << "Yes";
	else cout << "No";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}