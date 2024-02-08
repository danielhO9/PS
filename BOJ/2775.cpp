#include <bits/stdc++.h>
using namespace std;

int main() {
    int T, k, n; cin >> T;
    vector<long long> answer[15];
    for (long long i = 1; i < 15; ++i) answer[0].push_back(i);
    for (long long i = 1; i < 15; ++i) {
        for (long long j = 0; j < 14; ++j) {
            if (answer[i].empty()) answer[i].push_back(answer[i - 1][0]);
            else answer[i].push_back(answer[i].back() + answer[i - 1][j]);
        }
    }


    for (int i = 0; i < T; ++i) {
        cin >> k; cin >> n;
        cout << answer[k][n - 1] << "\n";
    }

    return 0;
}