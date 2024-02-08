#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    priority_queue<long long, vector<long long>, greater<long long>> arr;
    int N; cin >> N;
    long long temp;
    for (int i = 0; i < N; ++i) {
        cin >> temp;
        if (temp == 0 ) {
            if (arr.empty()) cout << 0 << "\n";
            else {
                cout << arr.top() << "\n";
                arr.pop();
            }
        } else {
            arr.push(temp);
        }
    }
    return 0;
}