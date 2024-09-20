#include <bits/stdc++.h>
using namespace std;

struct vertex {
	double dist;
	int v;
	int deg;
};

struct compare {
	bool operator()(const vertex& v1, const vertex& v2) {
		return v1.dist < v2.dist;
	}
};

vector<pair<int, double>> adj[100000];
double dist[100000][71];
priority_queue<vertex, vector<vertex>, compare> pq;
int par[100000];
bool reach[100000];

int find(int x) {
	if (par[x] == x) return x;
	par[x] = find(par[x]);
	return par[x];
}

void union_path(int x, int y) {
	x = find(x); y = find(y);
	par[x] = y;
}

double dijkstra(int N, int src, int K, vector<int>& arr) {

	for (int i = 0; i < N; ++i) for (int j = 0; j <= K; ++j) dist[i][j] = 1e15;

	double pow[K + 1]; pow[0] = 1.0;
	for (int i = 1; i <= K; ++i) pow[i] = pow[i - 1] / 2.0;

	dist[src][0] = 0.0;
	pq.push({0.0, src, 0});

	while(!pq.empty()) {
		double d = -pq.top().dist;
		int here = pq.top().v;
		int deg = pq.top().deg;
		pq.pop();

		if (dist[here][deg] < d) continue;
		if (arr[here] == 0) return d;

		for (auto& [there, c]: adj[here]) {
			if (!reach[there]) continue;
			
			double nextDist = d + c * pow[deg];
            if (dist[there][deg] > nextDist) {
				dist[there][deg] = nextDist;
				pq.push({-nextDist, there, deg});
			}
			
			if (arr[here] == 2 && deg < K) {
				nextDist = d + c * pow[deg + 1];
				if (dist[there][deg + 1] > nextDist) {
					dist[there][deg + 1] = nextDist;
					pq.push({-nextDist, there, deg + 1});
				}
			}
		}
	}
	return -1;
}

double solve(int N, int M, int K, int H, vector<int> x, vector<int> y, vector<int> c, vector<int> arr) {
	int k = min(K, 70);
	while (!pq.empty()) pq.pop();
	for (int i = 0; i < N; ++i) par[i] = i;
	for (int i = 0; i < N; ++i) adj[i].clear();
	for (int i = 0; i < M; ++i) {
		if (y[i] != H) adj[x[i]].push_back({y[i], c[i]});
		if (x[i] != H) adj[y[i]].push_back({x[i], c[i]});
		if (x[i] != H && y[i] != H) union_path(x[i], y[i]);
	}
	for (int i = 0; i < N; ++i) {
		if (find(i) == find(0)) reach[i] = true;
		else reach[i] = false;
	}
	arr[0] = 0;
	return dijkstra(N, H, k, arr);
}
