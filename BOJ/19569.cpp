#include <bits/stdc++.h>
using namespace std;

int cache[100001][500];

int matchCache(int n, int x) {
    int& ret = cache[n][x];
    if (ret != -1) return ret;
    if (n <= x) return ret = 1;
    for (int i = 1; i <= x; ++i) if (matchCache(n - i, i + 1) == 0) return ret = 1;
    return ret = 0;
}

int N;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    memset(cache, -1, sizeof(cache));
    if (!matchCache(N, 1)) {
        cout << "NO\n";
        cout.flush();
        return 0;
    }
    cout << "YES\n1\n";
    cout.flush();
    --N;
    while (true) {
        int x; cin >> x;
        N -= x;
        assert(matchCache(N, x + 1));
        if (N <= x + 1) {
            cout << N << '\n';
            cout.flush();
            break;
        } else {
            for (int i = 1; i <= x + 1; ++i) if (!matchCache(N - i, i + 1)) {
                cout << i << '\n';
                N -= i;
                cout.flush();
                break;
            }
        }
    }
}