#include <bits/stdc++.h>
using namespace std;

int N, M, T, K;
vector<int> y_x, x_y;
vector<int> dx = {0, 0, 1, 1};
vector<int> dy = {0, 1, 0, 1};

// 윗 꼭짓점의 좌표
int solution(int x, int y) {
    int ret = 0;
    for (int i = 0; i < T; ++i) {
        if (y - x - K <= y_x[i] && y_x[i] <= y - x &&
        x + y - K <= x_y[i] && x_y[i] <= x + y) {
            ret++;
        }
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int answer = 0; vector<int> answer_vec;
    cin >> N >> M >> T >> K;
    int A, B;
    for (int i = 0; i < T; ++i) {
        cin >> A >> B;
        y_x.push_back(B - A);
        x_y.push_back(A + B);
    }
    int x, y;
    for (int i: y_x) {
        for (int j: x_y) {
            x = (j - i) / 2; y = (i + j) / 2;
            if ((i + j) % 2 != 0) {
                for (int k = 0; k < 4; ++k) {
                    if (answer < solution(x + dx[k], y + dy[k])) {
                        answer = solution(x + dx[k], y + dy[k]);
                        answer_vec.clear();
                        answer_vec = {x + dx[k], y + dy[k] - K/2};
                    }
                }
            } else {
                if (answer < solution(x, y)) {
                    answer = solution(x, y);
                    answer_vec.clear();
                    answer_vec = {x, y - K/2};
                }
            }
        }
    }
    answer_vec[0] = max(answer_vec[0], 0);
    answer_vec[1] = max(answer_vec[1], 0);
    answer_vec[0] = min(answer_vec[0], N);
    answer_vec[1] = min(answer_vec[1], M);
    cout << answer_vec[0] << " " << answer_vec[1] << "\n";
    cout << answer;
    return 0;
}