#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);

    int N; cin >> N;
    vector<int> answer; int temp;
    for (int i = 0; i < 10001; ++i) {
        answer.push_back(0);
    }
    for (int i = 0; i < N; ++i) {
        cin >> temp;
        answer[temp] += 1;
    }
    for (int i = 1; i < 10001; ++i) {
        for (int j = 0; j < answer[i]; ++j) {
            cout << i << "\n";
        }
    }
    return 0;
}