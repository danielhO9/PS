#include <bits/stdc++.h>
using namespace std;
int N, M;
bool available(int y, int x) {
    if (y < N && y >= 0 && x < M && x >= 0) return true;
    return false;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int dy[4] = {1, 0, 0, -1};
    int dx[4] = {0, -1, 1, 0};
    cin >> N >> M;
    vector<vector<int>> paper(N, vector<int>(M, 0));
    deque<vector<int>> todo;
    for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
        cin >> paper[i][j];
        todo.push_back({i, j, 1, paper[i][j], -1});
    }
    int answer = 0;
    vector<int> now;
    while (!todo.empty()) {
        now = todo.front(); todo.pop_front();
        if (now[2] == 4) { answer = max(answer, now[3]); continue; }
        for (int i = 0; i < 4; ++i) {
            if (now[4] + i != 3 && available(now[0] + dy[i], now[1] + dx[i])) {
                todo.push_back({now[0] + dy[i], now[1] + dx[i], now[2] + 1, now[3] + paper[now[0] + dy[i]][now[1] + dx[i]], i});
            }
        }
    }
    int temp = 0; int to_erase; int cnt;
    for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
        temp = paper[i][j];
        to_erase = 1000;
        cnt = 0;
        for (int way = 0; way < 4; ++way) {
            if (available(i + dy[way], j + dx[way])) {
                cnt += 1;
                temp += paper[i + dy[way]][j + dx[way]];
                to_erase = min(to_erase, paper[i + dy[way]][j + dx[way]]);
            }
        }
        if (cnt == 4) temp -= to_erase;
        answer = max(answer, temp);
    }
    cout << answer;
    return 0;
}
/*
4 4
3 1 2 1
3 3 1 1
2 1 3 3
1 3 1 1
*/