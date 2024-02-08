#include <bits/stdc++.h>
using namespace std;

int main() {
    long long N; cin >> N; long long answer;
    answer = (-3 + sqrt(12 * N - 15)) / 6.0;
    if (N == 1) cout << 1;
    else cout << answer + 2;
    return 0;
}