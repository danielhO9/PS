#include <bits/stdc++.h>
using namespace std;

int V, E;
vector<int> graph[20001];
int visited[20001];

void dfs(int v, int t) {
    for (auto i: graph[v]) {
        if (visited[i] == 0) { visited[i] = t; dfs(i, -t); }
    }
}

void solution() {
    cin >> V >> E; int a, b;
    for (int i = 1; i <= V; ++i) { graph[i].clear(); visited[i] = 0; }
    for (int i = 0; i < E; ++i) {
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    for (int i = 1; i <= V; ++i) {
        if (visited[i] == 0) {
            visited[i] = 1;
            dfs(i, -1);
        }
    }
    for (int i = 1; i <= V; ++i) {
        for (auto j: graph[i]) {
            if (visited[i] + visited[j] != 0) {
                cout << "NO" << "\n";
                return;
            }
        }
    }
    cout << "YES" << "\n";
    return;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int K; cin >> K;
    for (int i = 0; i < K; ++i) solution();
}