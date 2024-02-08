#include <bits/stdc++.h>
using namespace std;

bool prime(int x) {
    int i = 2;
    if (x == 1) return false;
    if (x == 2) return true;
    while (i * i <= x) {
        if (x % i == 0) return false;
        ++i;
    }
    return true;
}

int main() {
    int N; cin >> N;
    int temp;
    int answer = 0;
    for (int i = 0; i < N; ++i) {
        cin >> temp;
        if (prime(temp)) answer += 1;
    }
    cout << answer << endl;
    return 0;
}