#include <bits/stdc++.h>
using namespace std;

int N, M;
int A[200000];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < N; ++i) cin >> A[i];
    int ans = A[N - 1] - A[0];
    int mn = A[0];
    for (int i = N - 1 - M; i < N; ++i) {
        mn = min(mn, A[i - N + 1 + M]);
        ans = max(A[i] - mn, ans);
    }
    cout << ans;
}