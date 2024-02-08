#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int N, M; cin >> N >> M;
    int a, b; vector<vector<int>> graph(N + 1, vector<int>(0));
    for (int i = 0; i < M; ++i) {
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    vector<int> answer(N + 1, 0); answer[0] = 10000;
    vector<bool> visited(N + 1);
    pair<int, int> now;
    deque<pair<int, int>> bfs;
    for (int i = 1; i <= N; ++i) {
        bfs = {{i, 0}}; fill(visited.begin(), visited.end(), false); visited[i] = true;
        while (!bfs.empty()) {
            now = bfs.front(); bfs.pop_front();
            answer[i] += now.second;
            for (int i: graph[now.first]) {
                if (!visited[i]) {
                    bfs.push_back({i, now.second + 1});
                    visited[i] = true;
                }
            }
        }
    }
    int min_value = *min_element(answer.begin(), answer.end());
    for (int i = 1; i <= N; ++i) {
        if (answer[i] == min_value) {
            cout << i;
            break;
        }
    }
    return 0;
}