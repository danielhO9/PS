#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int N, M; cin >> N >> M;
    vector<vector<int>> miro(N, vector<int>(M, 0));
    string temp;
    vector<pair<int, int>> way = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (int i = 0; i < N; ++i) {
        cin >> temp;
        for (int j = 0; j < M; ++j) {
            if (temp[j] == '1') miro[i][j] = 1;
        }
    }
    deque<pair<int, int>> bfs = {{0, 0}}; miro[0][0] = 11;
    pair<int, int> now;
    while (!bfs.empty()) {
        now = bfs.front(); bfs.pop_front();
        for (pair<int, int> w: way) {
            if (now.first + w.first >= 0 && now.first + w.first < N && now.second + w.second < M && now.second + w.second >= 0
            && miro[now.first + w.first][now.second + w.second] == 1) {
                miro[now.first + w.first][now.second + w.second] = miro[now.first][now.second] + 1;
                bfs.push_back({now.first + w.first, now.second + w.second});
            }
        }
    }
    cout << miro[N - 1][M - 1] - 10;

    return 0;
}