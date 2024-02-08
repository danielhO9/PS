#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> rectangle(25, vector<int>(25, 0));
int N;
vector<int> answer;
vector<pair<int, int>> way = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
pair<int, int> now;

int bfs(int y, int x) {
    int ansewr_temp = 0; rectangle[y][x] = 0;
    deque<pair<int, int>> todo = {{y, x}};
    while (!todo.empty()) {
        now = todo.front(); todo.pop_front(); ansewr_temp += 1;
        for (pair<int, int> element: way) {
            if (now.first + element.first < N && now.second + element.second < N && now.first + element.first >= 0 && now.second + element.second >= 0 && rectangle[now.first + element.first][now.second + element.second] == 1) {
                todo.push_back({now.first + element.first, now.second + element.second});
                rectangle[now.first + element.first][now.second + element.second] = 0;
            }
        }
    }
    return ansewr_temp;
}

int main() {
    cin >> N; string temp;
    for (int i = 0; i < N; ++i) {
        cin >> temp;
        for (int j = 0; j < N; ++j) if (temp[j] == '1') rectangle[i][j] = 1;
    }
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) if (rectangle[i][j] == 1) answer.push_back(bfs(i, j));
    cout << answer.size() << "\n";
    sort(answer.begin(), answer.end());
    for (int element: answer) cout << element << "\n";
    return 0;
}