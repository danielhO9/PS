#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int N, M; cin >> N >> M;
    vector<int> number(N + 1, 0);
    vector<int> S(N + 1, 0);
    for (int i = 1; i < N + 1; ++i) {
        cin >> number[i];
        S[i] = S[i - 1] + number[i];
    }
    int a, b;
    for (int i = 0; i < M; ++i) {
        cin >> a >> b;
        cout << S[b] - S[a - 1] << "\n";
    }
    return 0;
}