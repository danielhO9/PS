#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int N, A;
LL ans;
priority_queue<int, vector<int>, less<>> Q;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 1; i <= N; ++i) {
        cin >> A;
        Q.push(A - i);
        if (A < Q.top() + i) {
            ans += Q.top() - A + i;
            Q.pop(); Q.push(A - i);
        }
    }
    cout << ans;
}