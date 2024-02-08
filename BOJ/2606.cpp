#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int N, M; cin >> N >> M;
    vector<vector<int>> graph(N + 1, vector<int>(0));
    vector<bool> visited(N + 1, false); visited[1] = true;
    deque<int> bfs = {1};
    int a, b;
    for (int i = 0; i < M; ++i) {
        cin >> a >> b;
        graph[a].push_back(b); graph[b].push_back(a);
    }
    int now;
    while (!bfs.empty()) {
        now = bfs.front(); bfs.pop_front();
        for (int i: graph[now]) {
            if (!visited[i]) {
                visited[i] = true; bfs.push_back(i);
            }
        }
    }
    int answer = 0;
    for (bool i: visited) if (i) answer += 1;
    cout << answer - 1;

    return 0;
}