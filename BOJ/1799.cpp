#include <bits/stdc++.h>
using namespace std;
int n;
bool chess[10][10], ma[30], pa[30];

int solution(int v) {
    if (v == n * n - 1 || v == n * n - 2) {
        if (chess[v / n][v % n] && !ma[v / n - v % n + n] && !pa[v / n + v % n]) return 1;
        else return 0;
    }
    int ans = 0;
    if (chess[v / n][v % n] && !ma[v / n - v % n + n] && !pa[v / n + v % n]) {
        ma[v / n - v % n + n] = 1;
        pa[v / n + v % n] = 1;
        if (n % 2 == 0 && v % n == n - 1 && v + 1 < n * n) ans = max(ans, 1 + solution(v + 1));
        else if (n % 2 == 0 && v % n == n - 2 && v + 3 < n * n) ans = max(ans, 1 + solution(v + 3));
        else if (v + 2 < n * n) ans = max(ans, 1 + solution(v + 2));
        ma[v / n - v % n + n] = 0;
        pa[v / n + v % n] = 0;
    }
    if (n % 2 == 0 && v % n == n - 1 && v + 1 < n * n) ans = max(ans, solution(v + 1));
    else if (n % 2 == 0 && v % n == n - 2 && v + 3 < n * n) ans = max(ans, solution(v + 3));
    else if (v + 2 < n * n) ans = max(ans, solution(v + 2));
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> chess[i][j];
    if (n == 1) cout << solution(0);
    else cout << solution(0) + solution(1);
}