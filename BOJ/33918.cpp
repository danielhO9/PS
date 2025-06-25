#include <bits/stdc++.h>
using namespace std;

int N, M, C, D;
int b[200];
int cache[25001];
int ncache[25001];
deque<pair<int, int>> dq;

void add(int idx, int value) {
    while (!dq.empty() && dq.back().second < value) dq.pop_back();
    dq.push_back(make_pair(idx, value));
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M >> C >> D;
    for (int i = 0; i < N; ++i) cin >> b[i];
    for (int i = 1; i <= M; ++i) cache[i] = M - abs(b[0] - i);
    // for (int i = 1; i <= M; ++i) cout << cache[i] << ' ';
    // cout << '\n';
    for (int i = 1; i < N; ++i) {
        for (int j = 1; j <= C; ++j) {
            dq.clear();
            for (int k = j; k <= min(j + D, M); k += C) add(k, cache[k]);
            for (int k = j; k <= M; k += C) {
                int cur = dq.back().first + C;
                while (cur <= k + D && cur <= M) {
                    add(cur, cache[cur]);
                    cur += C;
                }
                while (dq.front().first < k - D) dq.pop_front();
                ncache[k] = dq.front().second + (M - abs(b[i] - k));
            }
        }
        swap(cache, ncache);
        // for (int j = 1; j <= M; ++j) cout << cache[j] << ' ';
        // cout << '\n';
    }
    int mx = 0;
    for (int i = 1; i <= M; ++i) mx = max(mx, cache[i]);
    cout << mx;
}