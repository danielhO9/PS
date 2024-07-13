#include <bits/stdc++.h>
using namespace std;

int find(vector<int>& parents, int x) {
	if (parents[x] == x) return x;
	parents[x] = find(parents, parents[x]);
	return parents[x];
}

void Union(vector<int>& parents, int x, int y) {
	x = find(parents, x); y = find(parents, y);
	int minn = min(x, y);
	parents[x] = minn; parents[y] = minn;
}

const double PI = 3.141592653589793238;

int x[1000], y[1000], r[1000];

double dist(pair<int, int> a, pair<int, int> b) { return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second)); }

double cost(int i, int j) {
	double rtor = dist({x[i], y[i]}, {x[j], y[j]});
	if ((double) r[i] + r[j] >= rtor - 1e-6) return 0.0;
	double dif = abs(r[i] - r[j]);
	double theta = acos(dif / rtor); theta *= 2.0;
	double ret = 2.0 * (sqrt(rtor * rtor - dif * dif));
	ret += (double) min(r[i], r[j]) * theta;
	ret += (double) max(r[i], r[j]) * (2.0 * PI - theta);
	return ret;
}

void solve() {
	int N; cin >> N;
	for (int i = 0; i < N; ++i) cin >> x[i] >> y[i] >> r[i];
	priority_queue<pair<double, pair<int, int>>> pq;
	for (int i = 0; i < N; ++i) for (int j = i + 1; j < N; ++j) {
		pq.push({-cost(i, j), {i, j}});
	}
	double ans = 0.0;
	int MAX_N = N;
	vector<int> parents(MAX_N);
	for (int i = 0; i < MAX_N; ++i) parents[i] = i;
	while (!pq.empty()) {
		auto edge = pq.top().second; double c = -pq.top().first; pq.pop();
		if (find(parents, edge.first) == find(parents, edge.second)) continue;
		ans += c;
		Union(parents, edge.first, edge.second);
	}
	cout<<fixed;
    cout.precision(7);
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}