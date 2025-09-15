#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, K;
ll A[300000], B[300000], C[300000];

void solve() {
    cin >> N >> K;
    for (int i = 0; i < N; ++i) cin >> A[i] >> B[i] >> C[i];
    priority_queue<pair<ll, ll>> pq;
    ll cur = 0;
    ll tm = 0;
    for (int i = 0; i < N; ++i) {
        while (!pq.empty() && -pq.top().first < A[i]) {
            cur -= pq.top().second;
            pq.pop();
        }
        tm = max(tm, A[i]);
        while (cur + C[i] > K) {
            cur -= pq.top().second;
            tm = max(tm, -pq.top().first);
            pq.pop();
        }
        cout << tm << '\n';
        pq.push(make_pair(-(tm + B[i]), C[i]));
        cur += C[i];
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}