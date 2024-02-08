#include <bits/stdc++.h>
using namespace std;
int N, ans[1000001], A;
priority_queue<int> Q;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 1; i <= N; ++i) {
        cin >> A; A -= i;
        Q.push(A);
        if (A < Q.top()) {
            Q.pop(); Q.push(A);
        }
        ans[i] = Q.top();
    }
    for (int i = N; i >= 1; --i) if (i != N) ans[i] = min(ans[i], ans[i + 1]);
    for (int i = 1; i <= N; ++i) cout << ans[i] + i << "\n";
}