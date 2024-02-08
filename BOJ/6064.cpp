#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL gcd(LL x, LL y) {
    if (x < y) return gcd(y, x);
    if (y == 0) return x;
    x %= y; return gcd(y, x);
}

LL solution(LL M, LL N, LL x, LL y) {
    if (M < N) return solution(N, M, y, x);
    LL year = x; LL limit = M * N / gcd(M, N);
    if (year == 0) year += M;
    while (year <= limit) {
        if (year % N == y) return year;
        year += M;
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    LL T, M, N, x, y;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        cin >> M >> N >> x >> y;
        cout << solution(M, N, x % M, y % N) << "\n";
    }
}