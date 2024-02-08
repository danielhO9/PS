#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int n, m, cache[101][101];
LL A[101], B[101];

int matchCache(int indexA, int indexB) {
    int& ret = cache[indexA][indexB];
    if (ret != -1) return ret;
    ret = 2;
    LL maximum = max(A[indexA], B[indexB]);
    for (int i = indexA + 1; i <= n; ++i) if (maximum < A[i]) ret = max(ret, matchCache(i, indexB) + 1);
    for (int i = indexB + 1; i <= m; ++i) if (maximum < B[i]) ret = max(ret, matchCache(indexA, i) + 1);
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int c; cin >> c;
    for (int i = 0; i < c; ++i) {
        memset(cache, -1, sizeof(cache));
        cin >> n >> m;
        A[0] = LLONG_MIN; B[0] = LLONG_MIN;
        for (int j = 1; j <= n; ++j) cin >> A[j];
        for (int j = 1; j <= m; ++j) cin >> B[j];
        cout << matchCache(0, 0) - 2 << "\n";
    }
    return 0;
}