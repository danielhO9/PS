#include <bits/stdc++.h>
using namespace std;

int p, q;
int cache[100][100][2];

// 0, q - 1
int matchCache(int i, int j, int t) {
    int& ret = cache[i][j][t];
    if (ret != INT32_MIN) return ret;
    if (t == 0) {
        for (int jj = j; jj < q; ++jj) {
            // (i, j) ~ (i, jj)
            int get;
            if ((i + 1) * (jj - j + 1) % 2 == 0) get = 0;
            else {
                if (j % 2) get = -1;
                else get = 1;
            }
            ret = max(ret, - (jj + 1 < q ? matchCache(i, jj + 1, 1) : 0) + get);
        }
    } else {
        for (int ii = i; ii >= 0; --ii) {
            // (i, j) ~ (ii, j)
            int get;
            if ((i - ii + 1) * (q - j) % 2 == 0) get = 0;
            else {
                if (q % 2) get = 1;
                else get = -1;
            }
            ret = max(ret, - (ii - 1 >= 0 ? matchCache(ii - 1, j, 0) : 0) + get);
        }
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> p >> q;
    for (int i = 0; i < p; ++i) for (int j = 0; j < q; ++j) for (int t = 0; t < 2; ++t) cache[i][j][t] = INT32_MIN;
    cout << matchCache(p - 1, 0, 0);
}