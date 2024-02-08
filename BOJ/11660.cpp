#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL N, table[1025][1025], M;

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    LL tempSum, temp;
    for (int i = 1; i <= N; ++i) {
        tempSum = 0;
        for (int j = 1; j <= N; ++j) {
            cin >> temp; tempSum += temp;
            table[i][j] = table[i - 1][j] + tempSum;
        }
    }
    int x1, y1, x2, y2;
    for (int i = 0; i < M; ++i) {
        cin >> x1 >> y1 >> x2 >> y2;
        cout << table[x2][y2] - table[x1 - 1][y2] - table[x2][y1 - 1] + table[x1 - 1][y1 - 1] << "\n";
    }
    return 0;
}