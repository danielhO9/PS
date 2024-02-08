#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M, V; cin >> N >> M >> V;
    vector<vector<int>> graph(N + 1, vector<int>(0));
    vector<bool> visited(N + 1, false);
    int a, b;
    for (int i = 0; i < M; ++i) {
        cin >> a >> b;
        graph[a].push_back(b); graph[b].push_back(a);
    }
    for (int i = 1; i <= N; ++i) sort(graph[i].rbegin(), graph[i].rend());
    vector<int> dfs; dfs.push_back(V); int now;
    while (!dfs.empty()) {
        now = dfs.back(); dfs.pop_back();
        if (visited[now]) continue;
        visited[now] = true;
        cout << now << " ";
        for (int i: graph[now]) {
            if (!visited[i]) {
                dfs.push_back(i);
            }
        }
    }
    cout << "\n";
    fill(visited.begin(), visited.end(), false);
    for (int i = 1; i <= N; ++i) sort(graph[i].begin(), graph[i].end());
    deque<int> bfs; bfs.push_back(V); visited[V] = true;
    while (!bfs.empty()) {
        now = bfs.front(); bfs.pop_front();
        cout << now << " ";
        for (int i: graph[now]) {
            if (!visited[i]) {
                bfs.push_back(i);
                visited[i] = true;
            }
        }
    }
}