#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, K; cin >> N >> K;
    int answer = 1;
    for (int i = 0; i < K; ++i) {
        answer *= N; --N;
    }
    for (int i = 1; i <= K; ++i) {
        answer /= i;
    }
    cout << answer;
    return 0;
}