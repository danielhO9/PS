#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> space(6, vector<int>(6, 0));
vector<bool> visited(7, false);
vector<int> dy = {1, -1, 0, 0};
vector<int> dx = {0, 0, 1, -1};
int answer;

bool isInRange(int y, int x) {
    if (0 <= y && y < 6 && 0 <= x && x < 6) { return true; }
    return false;
}

// y, x 전개도의 맞은편이 한 개 있다.
bool solution(int y, int x) {
    for (int i = 0; i < 7; ++i) visited[i] = false; visited[space[y][x]] = true;
    deque<vector<int>> todo;
    int eachAnswer = 0;
    for (int i = 0; i < 4; ++i) {
        if (isInRange(y + dy[i], x + dx[i]) && space[y + dy[i]][x + dx[i]] != 0) {
            todo.push_back({y + dy[i], x + dx[i], i});
            visited[space[y + dy[i]][x + dx[i]]] = true;
        }
    }
    vector<int> now;
    while (!todo.empty()) {
        now = todo.front(); todo.pop_front();
        for (int i = 0; i < 4; ++i) {
            if (isInRange(now[0] + dy[i], now[1] + dx[i])
            && space[now[0] + dy[i]][now[1] + dx[i]] != 0
            && !visited[space[now[0] + dy[i]][now[1] + dx[i]]]) {
                visited[space[now[0] + dy[i]][now[1] + dx[i]]] = true;
                if (i == now[2]) {
                    if (space[y][x] == 1) {
                        answer = space[now[0] + dy[i]][now[1] + dx[i]];
                    }
                    eachAnswer++; continue;
                }
                todo.push_back({now[0] + dy[i], now[1] + dx[i], now[2]});
            }
        }
    }
    if (eachAnswer == 1) return true;
    return false;
}



int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    for (int i = 0; i < 6; ++i) for (int j = 0; j < 6; ++j) {
        cin >> space[i][j];
        visited[space[i][j]] = true;
    }
    bool answerSwitch = true;
    for (int i = 0; i < 6; ++i) for (int j = 0; j < 6; ++j) {
        if (space[i][j] != 0) {
            answerSwitch = answerSwitch && solution(i, j);
            // cout << solution(i, j) << endl;
        }
    }
    if (answerSwitch) { cout << answer; }
    else { cout << 0; }

    return 0;
}