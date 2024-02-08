#include <bits/stdc++.h>
using namespace std;
int n, m;
int graph[1000][1000];
int nonVis[1000][1000];

bool available(int y, int x) {
    if (0 <= y && y < n && 0 <= x && x < m && nonVis[y][x] && graph[y][x] != 0) return true;
    return false;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m; deque<pair<pair<int, int>, int>> todo;
    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> graph[i][j]; 
            if (graph[i][j] != 0) nonVis[i][j] = true;
            if (graph[i][j] == 2) { todo.push_back({{i, j}, 0});  nonVis[i][j] = false; }
        }
    }
    while (!todo.empty()) {
        graph[todo.front().first.first][todo.front().first.second] = todo.front().second;
        for (int i = 0; i < 4; ++i) {
            if (available(todo.front().first.first + dy[i], todo.front().first.second + dx[i])) {
                todo.push_back({{todo.front().first.first + dy[i], todo.front().first.second + dx[i]}, todo.front().second + 1});
                nonVis[todo.front().first.first + dy[i]][todo.front().first.second + dx[i]] = false;
            }
        }
        todo.pop_front();
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (nonVis[i][j]) cout << -1 << " ";
            else cout << graph[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}