#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;
    vector<int> dp1(N), dp2(N);
    int temp;
    for (int i = 0; i < N; ++i) {
        cin >> temp;
        if (i == 0) dp1[i] = temp;
        else if (i == 1) {
            dp2[i] = temp;
            dp1[i] = dp1[i - 1] + temp;
        }
        else {
            dp1[i] = dp2[i - 1] + temp;
            dp2[i] = max(dp1[i - 2], dp2[i - 2]) + temp;
        }
    }
    cout << max(dp1[N - 1], dp2[N - 1]);
}