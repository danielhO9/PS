#include <bits/stdc++.h>
using namespace std;
int N, K;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> K;
    int ans = 0;
    for (int i = 1; i <= N; ++i) {
        ans = (ans + K) % i;
    }
    cout << ans + 1;
}