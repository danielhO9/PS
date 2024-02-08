#include <bits/stdc++.h>
using namespace std;

const int INF = 987654321;
const int MAX_V = 52;
int V;

int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];

int ctoi(char c) {
	if (c <= 'Z') return c - 'A';
	return c - 'a' + 26;
}

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


int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	V = 52; int N; cin >> N;
	char a, b; int F;
	for (int i = 0; i < N; ++i) {
		cin >> a >> b >> F;
		capacity[ctoi(a)][ctoi(b)] += F;
		capacity[ctoi(b)][ctoi(a)] += F;
	}
	cout << networkFlow(ctoi('A'), ctoi('Z'));
}