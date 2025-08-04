#include <bits/stdc++.h>
using namespace std;

int C, N;
int a[20], b[20], cache[3001];
const int MAX = 987654321;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> C >> N;
    for (int i = 0; i < N; ++i) cin >> a[i] >> b[i];
    for (int i = 0; i <= C + 1000; ++i) cache[i] = MAX;
    cache[0] = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 1; j <= C + 1000; ++j) if (j >= b[i]) {
            cache[j] = min(cache[j], cache[j - b[i]] + a[i]);
        }
    }
    int ans = INT32_MAX;
    for (int i = C; i <= C + 1000; ++i) ans = min(ans, cache[i]);
    cout << ans;
}