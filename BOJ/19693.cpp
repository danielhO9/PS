#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL N, H, ans, S, Sl, Sr;
priority_queue<LL, vector<LL>, less<>> l;
priority_queue<LL, vector<LL>, greater<>> r;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> H;
    for (LL i = 1; i <= N; ++i) {
        cin >> S;
        Sl = S - (N - i) * H;
        Sr = S + (N - i) * H;
        if (i == 1) {
            l.push(Sl); r.push(Sr);
            continue;
        }
        if (Sl < l.top()) {
            ans += l.top() - Sl;
            r.push(l.top() + (N - i) * 2 * H);
            l.pop(); l.push(Sl); l.push(Sl);
        } else if (r.top() < Sr) {
            ans += Sr - r.top();
            l.push(r.top() - (N - i) * 2 * H);
            r.pop(); r.push(Sr); r.push(Sr);
        } else {
            l.push(Sl); r.push(Sr);
        }
    }
    cout << ans;
    return 0;
}