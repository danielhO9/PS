#include <bits/stdc++.h>
using namespace std;
int N; vector<int> ground = {0};
vector<pair<int, int>> answer;

void solution(vector<int>& ground, vector<pair<int, int>> his) {
    if (!answer.empty()) return;
    vector<int> reversePoint;
    for (int i = 1; i <= N; ++i) {
        if (abs(ground[i] - ground[i - 1]) != 1) reversePoint.push_back(i);
        if (i == N && ground[i] != N) reversePoint.push_back(N + 1);
    }
    if (reversePoint.empty()) { answer = his; return; }
    if (his.size() == 0 && reversePoint.size() > 4) return;
    if (his.size() == 1 && reversePoint.size() > 2) return;
    if (his.size() == 2) return;
    for (int i: reversePoint) {
        for (int j: reversePoint) {
            if (i > j) continue;

            if (i == j) his.push_back({i, j});
            else his.push_back({i, j - 1});
            reverse(ground.begin() + i, ground.begin() + j);
            solution(ground, his);
            his.pop_back();
            reverse(ground.begin() + i, ground.begin() + j);

            his.push_back({i, j});
            reverse(ground.begin() + i, ground.begin() + j + 1);
            solution(ground, his);
            his.pop_back();
            reverse(ground.begin() + i, ground.begin() + j + 1);
            if (i > 1) {
                his.push_back({i - 1, j - 1});
                reverse(ground.begin() + i - 1, ground.begin() + j);
                solution(ground, his);
                his.pop_back();
                reverse(ground.begin() + i - 1, ground.begin() + j);
            }
        }
    }

}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N; int num;
    for (int i = 1; i <= N; ++i) {
        cin >> num;
        ground.push_back(num);
    }
    solution(ground, {});
    for (pair<int, int> i: answer) {
        cout << i.first << " " << i.second << "\n";
    }
    if (answer.size() == 0) {
        cout << 1 << " " << 1 << "\n";
        cout << 1 << " " << 1 << "\n";
    }
    return 0;
}
// 1 2 3 4 5 6 7
// 1 5 4 3 2 6 7
// 1 5 6 2 3 4 7