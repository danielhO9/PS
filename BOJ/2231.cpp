#include <bits/stdc++.h>
using namespace std;

int main() {
    int N; cin >> N; int answer = 0;
    for (int i = min(1, N - 60); i < N; ++i) {
        answer = i;
        int temp = i;
        for (int j = 1; j < 8; ++j) {
            answer += temp % 10;
            temp /= 10;
        }
        if (answer == N) {
            cout << i;
            break;
        }
    }
    if (answer != N) cout << 0;

    return 0;
}