#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> paper(128, vector<int>(128, 0));
int N;
int answer_blue = 0, answer_white = 0; int temp;

void solution(int y, int x, int size) {
    temp = paper[y][x];
    for (int i = y; i < y + size; ++i) for (int j = x; j < x + size; ++j) if (paper[i][j] != temp) {
        solution(y, x, size / 2); solution(y, x + size / 2, size / 2); solution(y + size / 2, x, size / 2); solution(y + size / 2, x + size / 2, size / 2);
        return;
    }
    if (temp) answer_blue++;
    else answer_white++;
    return;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> paper[i][j];
    solution(0, 0, N);
    cout << answer_white << "\n" << answer_blue;
    return 0;
}