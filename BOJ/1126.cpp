#include <bits/stdc++.h>
using namespace std;
int cache[50][250001], N;
int height[50];

void dp(int n) {
    if (height[n] <= 250000) cache[n][height[n]] = max(height[n], cache[n][height[n]]);
    if (n == 0) return;
    for (int i = 0; i <= 250000; ++i) cache[n][i] = max(cache[n][i], cache[n - 1][i]);
    if (height[n] > 250000) return;
    for (int i = 0; i <= 250000; ++i) {
        if (cache[n - 1][i] != 0) {
            if (i + height[n] <= 250000) cache[n][i + height[n]] = max(cache[n][i + height[n]], cache[n - 1][i] + height[n]);
            if (abs(i - height[n]) <= 250000 && height[n] > i) cache[n][abs(i - height[n])] = max(cache[n][abs(i - height[n])], cache[n - 1][i] - i + height[n]);
            else if (abs(i - height[n]) <= 250000) cache[n][abs(i - height[n])] = max(cache[n][abs(i - height[n])], cache[n - 1][i]);
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> height[i];
    for (int i = 0; i < N; ++i) dp(i);
    int answer = 0;
    for (int i = 0; i < N; ++i) answer = max(answer, cache[i][0]);
    if (answer == 0) --answer;
    cout << answer;
    return 0;
}