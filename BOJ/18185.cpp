#include <bits/stdc++.h>
using namespace std;
int N, A[10002], ans;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> A[i];
    int temp;
    for (int i = 0; i < N; ++i) {
        if (A[i + 1] > A[i + 2]) {
            temp = min(A[i], A[i + 1] - A[i + 2]);
            ans += temp * 5;
            A[i] -= temp; A[i + 1] -= temp;
        }
        temp = min({A[i], A[i + 1], A[i + 2]});
        ans += temp * 7;
        A[i] -= temp; A[i + 1] -= temp; A[i + 2] -= temp;
        ans += A[i] * 3; A[i] = 0;
    }
    cout << ans;
}