#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll N; cin >> N;
    ll answer = 0;
    ll start = 1, end = 1; ll temp = 1;
    while (start != N) {
        if (temp < N) {
            end++;
            temp += end;
        } else if (temp == N) {
            answer += 1;
            end++;
            temp += end;
        } else {
            temp -= start;
            start++;
        }
    }
    cout << answer + 1;
    return 0;
}