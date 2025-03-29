#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
int P[100];
int ans[100];

void solve() {
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> P[i];
    int r = 1;
    priority_queue<pair<int, int>> pq;
    for (int i = 0; i < N; ++i) pq.push({P[i], i});
    while (!pq.empty()) {
        int val = pq.top().first;
        int cnt = 0;
        while (!pq.empty() && pq.top().first== val) {
            ans[pq.top().second] = r; ++cnt; pq.pop();
        }
        r += cnt;
    }
    for (int i = 0; i < N; ++i) cout << ans[i] << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}