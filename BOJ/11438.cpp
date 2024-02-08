#include <bits/stdc++.h>
using namespace std;

int N;
vector<int> graph[100001]; vector<int> dep(100001);
vector<vector<int>> parents(100001, vector<int>(17, 0));

void dfs(int v, int p) {
    parents[v][0] = p; dep[v] = dep[p] + 1;
    for (int i: graph[v]) if (i != p) dfs(i, v);
}

void getParents(int num) {
    for (int i = 1; i <= N; ++i) parents[i][num] = parents[parents[i][num - 1]][num - 1];
}

int LCA(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int dif = dep[u] - dep[v];
    for (int i = 0; dif; ++i) {
        if (dif % 2) u = parents[u][i];
        dif /= 2;
    }
    if (u != v) {
        for (int i = 16; i >= 0; --i) {
            if (parents[u][i] != 0 && parents[u][i] != parents[v][i]) {
                u = parents[u][i]; v = parents[v][i];
            }
        }
        u = parents[u][0];
    }
    return u;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N; int x, y;
    for (int i = 0; i < N - 1; ++i) {
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    dep[0] = -1; dfs(1, 0);
    for (int i = 1; i < 17; ++i) getParents(i);
    int M; cin >> M;
    for (int i = 0; i < M; ++i) {
        cin >> x >> y;
        cout << LCA(x, y) << "\n";
    }
    return 0;
}