#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int N, M, A, B; cin >> N >> M >> A >> B;
    int ans = 0;
    int dif = max(3 * N - M, 0);
    if (dif) ans += dif * A + B;
    cout << ans;
}