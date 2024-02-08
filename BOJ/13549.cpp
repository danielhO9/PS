#include <bits/stdc++.h>
using namespace std;

int N, K, dis[200001];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> Q;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> K;
	for (int i = 0; i <= 200000; ++i) dis[i] = INT32_MAX;
	Q.push({0, N}); dis[N] = 0;
	int v, d;
	while (!Q.empty()) {
		d = Q.top().first; v = Q.top().second;
		Q.pop();
		if (dis[v] < d) continue;
		if (v - 1 >= 0 && dis[v - 1] > d + 1) {
			Q.push({d + 1, v - 1});
			dis[v - 1] = d + 1;
		}
		if (v + 1 <= 200000 && dis[v + 1] > d + 1) {
			Q.push({d + 1, v + 1});
			dis[v + 1] = d + 1;
		}
		if (v * 2 <= 200000 && dis[v * 2] > d) {
			Q.push({d, v * 2});
			dis[v * 2] = d;
		} 
	}
	cout << dis[K];
}