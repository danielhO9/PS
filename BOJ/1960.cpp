#include <bits/stdc++.h>
using namespace std;

const int INF = 987654321;
const int MAX_V = 1002;
int V, n, temp1, temp2;

int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];

int networkFlow(int source, int sink) {
	memset(flow, 0, sizeof(flow));
	int totalFlow = 0;
	while (true) {
		vector<int> parent(MAX_V, -1);
		queue<int> q;
		parent[source] = source;
		q.push(source);
		while (!q.empty() && parent[sink] == -1) {
			int here = q.front(); q.pop();
			for (int there = 0; there < V; ++there) {
				if (capacity[here][there] - flow[here][there] > 0 && parent[there] == -1) {
					q.push(there);
					parent[there] = here;
				}
			}
		}
		if (parent[sink] == -1) break;
		int amount = INF;
		for (int p = sink; p != source; p = parent[p]) {
			amount = min(capacity[parent[p]][p] - flow[parent[p]][p], amount);
		}
		for (int p = sink; p != source; p = parent[p]) {
			flow[parent[p]][p] += amount;
			flow[p][parent[p]] -= amount;
		}
		totalFlow += amount;
	}
	return totalFlow;
}

bool check() {
	if (temp1 != temp2) return false;
	if (temp1 != networkFlow(0, 1)) return false;
	// for (int i = 2; i < n + 2; ++i) for (int j = n + 2; j < 2 * n + 2; ++j) if (flow[i][j] < 0) return false;
	return true;
}


int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n; V = 2 * n + 2;
	for (int i = 0; i < n; ++i) { cin >> capacity[0][2 + i]; temp1 += capacity[0][2 + i]; }
	for (int i = 0; i < n; ++i) { cin >> capacity[n + i + 2][1]; temp2 += capacity[n + i + 2][1]; }
	for (int i = 2; i < n + 2; ++i) for (int j = n + 2; j < 2 * n + 2; ++j) { capacity[i][j] = 1; }
	if (!check()) cout << -1;
	else {
		cout << 1 << '\n';
		for (int i = 2; i < n + 2; ++i) {
			for (int j = n + 2; j < 2 * n + 2; ++j) cout << flow[i][j];
			cout << '\n';
		}
	}
}