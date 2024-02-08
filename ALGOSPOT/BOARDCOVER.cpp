#include <bits/stdc++.h>
using namespace std;
int H, W;
vector<vector<int>> game(20, vector<int>(20, 0));

bool possible(int y, int x) {
    if (0 <= y && y < H && 0 <= x && x < W && game[y][x] == 0) return true;
    return false;
}
const int coverType[4][3][2] = {
    {{0, 0}, {1, 0}, {0, 1}},
    {{0, 0}, {0, 1}, {1, 1}},
    {{0, 0}, {1, 0}, {1, 1}},
    {{0, 0}, {1, 0}, {1, -1}}
};

int solution() {
    int answer = 0; bool checker = false;
    pair<int, int> now = {H, W};
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (game[i][j] == 0) { now = {i, j}; checker = true; break; }
        }
        if (checker) break;
    }
    if (now.first == H) { return 1; }
    int temp_y, temp_x; double ok = true;
    for (int i = 0; i < 4; ++i) {
        ok = true;
        for (int j = 0; j < 3; ++j) {
            temp_y = now.first + coverType[i][j][0]; temp_x = now.second + coverType[i][j][1];
            if (!possible(temp_y, temp_x)) ok = false;
        }
        if (ok) {
            for (int j = 0; j < 3; ++j) {
                temp_y = now.first + coverType[i][j][0]; temp_x = now.second + coverType[i][j][1];
                game[temp_y][temp_x] = 1;
            }
            answer += solution();
            for (int j = 0; j < 3; ++j) {
                temp_y = now.first + coverType[i][j][0]; temp_x = now.second + coverType[i][j][1];
                game[temp_y][temp_x] = 0;
            }
        }
    }
    return answer;
}

int main() {
    int C; cin >> C; string temp;
    for (int i = 0; i < C; ++i) {
        cin >> H >> W;
        for (int j = 0; j < H; ++j) {
            cin >> temp;
            for (int k = 0; k < W; ++k) {
                if (temp[k] == '#') game[j][k] = 1;
                else game[j][k] = 0;
            }
        }
        cout << solution() << "\n";
    }
}