#include <bits/stdc++.h>
using namespace std;

vector<int> clocks(10);
int answer = 40;
vector<int> answer_vec(40, 0);

vector<vector<int>> moving = {
    {0, 1, 3, 4},
    {0, 1, 2},
    {1, 2, 4, 5},
    {0, 3, 6},
    {1, 3, 4, 5, 7},
    {2, 5, 8},
    {3, 4, 6, 7},
    {6, 7, 8},
    {4, 5, 7, 8}
};

void do_move(int cnt) {
    for (int element: moving[cnt]) clocks[element] = (clocks[element] + 1) % 4;
}

void solution(vector<int> ret, int x) {
    if (x == 9) {
        for (int element: clocks) if (element != 0) return;
        if (answer > ret.size()) {
            answer = ret.size();
            for (int i = 0; i < ret.size(); ++i) {
                answer_vec[i] = ret[i];
            }
        }
        return;
    }
    for (int i = 0; i < 4; ++i) {
        solution(ret, x + 1);
        do_move(x);
        ret.push_back(x);
    }
    return;
}

int main() {
    for (int i = 0; i < 9; ++i) cin >> clocks[i];
    solution({}, 0);
    for (int i = 0; i < answer; ++i) {
        cout << answer_vec[i] + 1 << " ";
    }
    return 0;
}