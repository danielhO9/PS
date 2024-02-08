#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> dx = {-1, 1, 0, 0};
    vector<int> dy = {0, 0, -1, 1};
    int M, N; cin >> M >> N;
    vector<vector<int>> storage(N, vector<int>(M, 0));
    deque<vector<int>> todo;
    for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
        cin >> storage[i][j];
        if (storage[i][j] == 1) { todo.push_back({i, j, 0}); }
    }
    vector<int> now;
    int temp_dy, temp_dx;
    int answer = 0;
    while (!todo.empty()) {
        now = todo.front(); todo.pop_front();
        answer = now[2];
        for (int i = 0; i < 4; ++i) {
            temp_dy = now[0] + dy[i]; temp_dx = now[1] + dx[i];
            if (temp_dy < N && temp_dy >= 0 && temp_dx < M && temp_dx >= 0 && storage[temp_dy][temp_dx] == 0) {
                storage[temp_dy][temp_dx] = 1;
                todo.push_back({temp_dy, temp_dx, now[2] + 1});
            }
        }
    }
    bool done = true;
    for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) if (storage[i][j] == 0) done = false;
    if (done) cout << answer;
    else cout << -1;
}