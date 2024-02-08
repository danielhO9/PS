#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;
    vector<int> answer(N, 1e8);
    vector<pair<int, int>> board;
    vector<int> x, y; int a, b;
    for (int i = 0; i < N; ++i) {
        cin >> a >> b;
        board.push_back({a, b});
        x.push_back(a); y.push_back(b);
    }
    vector<int> temp;
    for (int i: x) for (int j: y) {
        temp.clear(); temp.shrink_to_fit();
        for (pair<int, int> cordinate: board) {
            temp.push_back(abs(cordinate.first - i) + abs(cordinate.second - j));
        }
        sort(temp.begin(), temp.end());
        for (int k = 0; k < N; ++k) {
            if (k != 0) temp[k] = temp[k - 1] + temp[k];
            answer[k] = min(answer[k], temp[k]);
        }
    }
    for (int i = 0; i < N; ++i) cout << answer[i] << " ";
    return 0;
}