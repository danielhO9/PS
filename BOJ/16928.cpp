#include <bits/stdc++.h>
using namespace std;
int N, M, p[101], visited[101];
deque<pair<int, int>> Q;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M; int a, b;
    for (int i = 0; i < N + M; ++i) {
        cin >> a >> b; p[a] = b;
    }
    Q.push_back({1, 0}); visited[1] = 1; int temp;
    while(!Q.empty()) {
        if (Q.front().first == 100) {
            cout << Q.front().second;
            break;
        }
        for (int i = 1; i <= 6; ++i) {
            if ((Q.front().first + i) <= 100 && !visited[Q.front().first + i]) {
                temp = Q.front().first + i; visited[temp] = 1;
                while (p[temp] > 0) {
                    visited[p[temp]] = 1;
                    temp = p[temp];
                }
                Q.push_back({temp, Q.front().second + 1});
            }
        }
        Q.pop_front();
    }
}