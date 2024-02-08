#include <bits/stdc++.h>
using namespace std;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> Q;
int N;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N; int temp;
    for (int i = 0; i < N; ++i) {
        cin >> temp;
        if (temp == 0) {
            if (Q.empty()) cout << 0 << "\n";
            else {
                cout << Q.top().second << "\n";
                Q.pop();
            }
        } else {
            Q.push({abs(temp), temp});
        }
    }
}