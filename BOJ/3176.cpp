#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int N;
vector<pair<int, LL>> graph[100000];
int dep[100000], parents[100000][17]; LL dis[100000];
LL maxD[100000][17], minD[100000][17], maxAns, minAns;

void dfs(int v, int p, LL d) {
    parents[v][0] = p;
	maxD[v][0] = d;
	minD[v][0] = d;
    if (p == -1) {
        dep[v] = 1; dis[v] = 0LL;
    } else {
        dep[v] = dep[p] + 1; dis[v] = dis[p] + d;
    }
    for (auto [i, nd]: graph[v]) if (i != p) dfs(i, v, nd);
}

void getParents(int num) {
    for (int i = 0; i < N; ++i) {
        if (parents[i][num - 1] == -1) parents[i][num] = -1;
        else {
			parents[i][num] = parents[parents[i][num - 1]][num - 1];
			maxD[i][num] = max(maxD[i][num - 1], maxD[parents[i][num - 1]][num - 1]);
			minD[i][num] = min(minD[i][num - 1], minD[parents[i][num - 1]][num - 1]);
		}
    }
}

void LCA(int u, int v) {
	maxAns = 0; minAns = LLONG_MAX;
    if (dep[u] < dep[v]) swap(u, v);
    int dif = dep[u] - dep[v];
    for (int i = 0; dif; ++i) {
        if (dif % 2) {
			maxAns = max(maxAns, maxD[u][i]);
			minAns = min(minAns, minD[u][i]);
			u = parents[u][i];
		}
        dif /= 2;
    }
    if (u != v) {
        for (int i = 16; i >= 0; --i) {
            if (parents[u][i] != -1 && parents[u][i] != parents[v][i]) {
				maxAns = max(maxAns, maxD[u][i]);
				minAns = min(minAns, minD[u][i]);
				maxAns = max(maxAns, maxD[v][i]);
				minAns = min(minAns, minD[v][i]);
                u = parents[u][i]; v = parents[v][i];
            }
        }
		maxAns = max(maxAns, maxD[v][0]);
		minAns = min(minAns, minD[v][0]);
		maxAns = max(maxAns, maxD[u][0]);
		minAns = min(minAns, minD[u][0]);
        u = parents[u][0];
    }
	return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	int A, B; LL C;
	for (int i = 0; i < N - 1; ++i) {
		cin >> A >> B >> C;
		--A; --B;
		graph[A].push_back({B, C});
		graph[B].push_back({A, C});
	}
	dfs(0, -1, 0LL); for (int i = 1; i < 17; ++i) getParents(i);
	int K; cin >> K;
	for (int i = 0; i < K; ++i) {
		cin >> A >> B;
		--A; --B;
		LCA(A, B);
		cout << minAns << ' ' << maxAns << '\n';
	}
}