#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int n, d, A;
LL ans;
priority_queue<int, vector<int>, less<>> Ql;
priority_queue<int, vector<int>, greater<>> Qr;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> A;
        Ql.push(A - i * d);
        Qr.push(A + i * d);
        if (A < Ql.top() + i * d) {
            ans += Ql.top() - A + i;
            Ql.pop(); Ql.push(A - i);
        }
    }
    cout << ans;
}