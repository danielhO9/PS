#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL N, B, C, A[1000002], ans;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> B >> C;
    for (int i = 0; i < N; ++i) cin >> A[i];
    if (B <= C) {
        for (int i = 0; i < N; ++i) ans += A[i] * B;
        cout << ans;
    } else {
        LL temp;
        for (int i = 0; i < N; ++i) {
            if (A[i + 1] > A[i + 2]) {
                temp = min(A[i], A[i + 1] - A[i + 2]);
                ans += temp * (B + C);
                A[i] -= temp; A[i + 1] -= temp;
            }
            temp = min({A[i], A[i + 1], A[i + 2]});
            ans += temp * (B + 2 * C);
            A[i] -= temp; A[i + 1] -= temp; A[i + 2] -= temp;
            ans += A[i] * B; A[i] = 0;
        }
        cout << ans;
    }
}