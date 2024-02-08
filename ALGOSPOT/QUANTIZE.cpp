#include <bits/stdc++.h>
using namespace std;
int N, S, arr[101], sum[101], square[101], cache[101][11];
int INF = 987654321;

int calc(int start, int end) {
    int psum = sum[end] - sum[start - 1];
    int psquare = square[end] - square[start - 1];
    int m = int(0.5 + (double) psum / (end - start + 1));
    return psquare - 2 * m * psum + m * m * (end - start + 1);
}

int matchCache(int n, int s) {
    if (n > N) return 0;
    int& ret = cache[n][s];
    if (ret != -1) return ret;
    if (s == 1) return ret = calc(n, N);
    ret = INF;
    for (int i = n; i <= N; ++i) ret = min(ret, calc(n, i) + matchCache(i + 1, s - 1));
    return ret;
}


int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int C; cin >> C;
    for (int i = 0; i < C; ++i) {
        cin >> N >> S;
        for (int j = 1; j <= N; ++j) cin >> arr[j];
        sort(arr, arr + N + 1);
        for (int j = 1; j <= N; ++j) {
            sum[j] = sum[j - 1] + arr[j];
            square[j] = square[j - 1] + arr[j] * arr[j];
        }
        memset(cache, -1, sizeof(cache));
        cout << matchCache(1, S) << "\n";
    }
    return 0;
}