#include <bits/stdc++.h>
using namespace std;
int N, K, light[200];
int cache[200][200];

int matchCache(int start, int end) {
    if (start == end) return 0;
    int& ret = cache[start][end];
    if (ret != -1) return ret;
    ret = 987654321;
    for (int i = start; i < end; ++i) {
        if (light[start] == light[end]) ret = min(ret, matchCache(start, i) + matchCache(i + 1, end));
        else ret = min(ret, matchCache(start, i) + matchCache(i + 1, end) + 1);
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> K;
    for (int i = 0; i < N; ++i) cin >> light[i];
    memset(cache, -1, sizeof(cache));
    cout << matchCache(0, N - 1);
    return 0;
}