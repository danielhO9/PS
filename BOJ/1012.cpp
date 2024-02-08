#include <bits/stdc++.h>
using namespace std;

int main() {
    ios:: sync_with_stdio(false); cin.tie(NULL);

    int T; cin >> T;
    int M, N, K, x, y;
    vector<pair<int, int>> queue; int answer;
    vector<pair<int, int>> way = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (int i = 0; i < T; ++i) {
        queue.clear(); answer = 0;
        cin >> M >> N >> K;
        vector<vector<bool>> ground(N, vector<bool>(M, false));
        for (int j = 0; j < K; ++j) {
            cin >> x >> y;
            ground[y][x] = true;
        }
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < M; ++k) {
                if (ground[j][k]) {
                    answer += 1;
                    queue.push_back({j, k}); pair<int, int> now;
                    while (!queue.empty()) {
                        now = queue.back(); queue.pop_back();
                        for (pair<int, int> element: way) {
                            if (0 <= now.first + element.first && now.first + element.first <N && 0<= now.second + element.second && now.second + element.second < M && ground[now.first + element.first][now.second + element.second]) {
                                ground[now.first + element.first][now.second + element.second] = false;
                                queue.push_back({now.first + element.first, now.second + element.second});
                            }
                        }
                    }
                }
            }
        }
        cout << answer << "\n";
    }


    return 0;
}