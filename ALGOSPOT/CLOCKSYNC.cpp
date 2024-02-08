#include <bits/stdc++.h>
using namespace std;

// 스위치별로 바꾸는 시계
vector<vector<int>> switches = {
    {0, 1, 2},
    {3, 7, 9, 11},
    {4, 10, 14, 15},
    {0, 4, 5, 6, 7},
    {6, 7, 8, 10, 12},
    {0, 2, 14, 15},
    {3, 14, 15},
    {4, 5, 7, 14, 15},
    {1, 2, 3, 4, 5},
    {3, 4, 5, 9, 13}
};

// 각 시계마다 영향을 받는 스위치
vector<vector<int>> control = {
    {0, 3, 5},
    {0, 8},
    {0, 5, 8},
    {1, 6, 8, 9},
    {2, 3, 7, 8, 9},
    {3, 7, 8, 9},
    {3, 4},
    {1, 3, 4, 7},
    {4},
    {1, 9},
    {2, 4},
    {1},
    {4},
    {9},
    {2, 5, 6, 7},
    {2, 5, 6, 7}
};
// 4 2 1 9 3 7 8 0 5 6

// 시계가 가리키는 값
vector<int> clocks(16, 0);

void do_switch(int num, int cnt) {
    for (int i: switches[num]) clocks[i] = ((clocks[i] + cnt) % 4);
}

// 해당 스위치는 더이상 누르지 않는다
vector<bool> visited(10, false);

int solution() {
    int answer = 0; int i = 0; int todo_swi;
    while (true) {
        todo_swi = -1;
        bool ok = true;
        for (int swi: control[i]) {
            if (!visited[swi] && todo_swi == -1) todo_swi = swi;
            else if (!visited[swi]) { ok = false; break; }
        }
        if (todo_swi != -1 && ok) { 
            // cout << i << " : " << todo_swi << " " << (4 - clocks[i]) % 4 << endl;
            answer += (4 - clocks[i]) % 4;
            do_switch(todo_swi, (4 - clocks[i]) % 4);
            visited[todo_swi] = true;
        }
        i += 1; i %= 16;
        bool done = true;
        for (int j = 0; j < 10; ++j) {
            if (!visited[j]) { done = false; break; }
        }
        if (done) break;
    }
    for (int time: clocks) {
        if (time != 0) return -1;
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int C; cin >> C;
    for (int i = 0; i < C; ++i) {
        for (int j = 0; j < 16; ++j) visited[j] = false;
        for (int j = 0; j < 16; ++j) {
            cin >> clocks[j];
            clocks[j] = (clocks[j] / 3) % 4;
        }
        cout << solution() << "\n";
    }
    return 0;
}