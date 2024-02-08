#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int N, M; cin >> N >> M;
    vector<bool> visited(N + 1, false);
    vector<vector<int>> graph(N + 1, vector<int>(0));

    int a, b;
    for (int i = 0; i < M; ++i) {
        cin >> a >> b;
        graph[a].push_back(b); graph[b].push_back(a);
    }
    int answer = 0; deque<int> todo; int now;
    for (int i = 1; i < N + 1; ++i) {
        if (!visited[i]) {
            answer += 1; visited[i] = true;
            todo.push_back(i);
            while (!todo.empty()) {
                now = todo.front(); todo.pop_front();
                for (int element: graph[now]) {
                    if (!visited[element]) {
                        visited[element] = true; todo.push_back(element);
                    } 
                }
            }
        }
    }
    cout << answer;
    return 0;
}