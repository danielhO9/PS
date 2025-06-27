#include <bits/stdc++.h>
using namespace std;

int C, N;
int T[20000], A[20000], B[20000];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> C >> N;
    for (int i = 0; i < C; ++i) cin >> T[i];
    for (int i = 0; i < N; ++i) cin >> A[i] >> B[i];
    vector<pair<int, int>> v;
    for (int i = 0; i < N; ++i) v.push_back(make_pair(A[i], B[i]));
    sort(v.begin(), v.end());
    int idx = 0;
    sort(T, T + C);
    int ans = 0;
    priority_queue<int> pq;
    for (int i = 0; i < C; ++i) {
        while (idx < N && v[idx].first <= T[i]) {
            pq.push(-v[idx].second);
            ++idx;
        }
        while (!pq.empty()) {
            auto tmp = pq.top(); pq.pop();
            if (-tmp < T[i]) continue;
            else {
                ++ans;
                break;
            }
        }
    }
    cout << ans;
}