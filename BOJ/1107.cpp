#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int N, M; cin >> N; cin >> M;
    vector<bool> button(10, true);
    int temp;
    for (int i = 0; i < M; ++i) {
        cin >> temp;
        button[temp] = false;
    }
    int answer = abs(N - 100);
    deque<pair<int, int>> possible;
    for (int i = 0; i < 10; ++i) {
        if (button[i]) {
            possible.push_back({i, 1});
            answer = min(answer, 1 + abs(N - i));
        }
    }
    pair<int, int> now;
    while (!possible.empty()) {
        now = possible.front();
        possible.pop_front();
        if (now.second < 6) {
            for (int i = 0; i < 10; ++i) {
                if (button[i]) {
                    possible.push_back({now.first * 10 + i, now.second + 1});
                    answer = min(answer, now.second + 1 + abs(N - now.first * 10 - i));
                }
            }
        }
    }
    cout << answer;

    return 0;
}