#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, R;
int L[200001];

void solve() {
    cin >> N >> R;
    for (int i = 1; i <= N; ++i) cin >> L[i];
    int l = 0;
    for (int i = 1; i <= N; ++i) {
        if (L[i] == 0) {
            l = i;
            break;
        }
    }
    if (l == 0) {
        cout << 0;
        return;
    }
    int r = 0;
    for (int i = N; i >= 1; --i) {
        if (L[i] == 0) {
            r = i;
            break;
        }
    }
    assert(l <= r);
    l = min(l, R + 1);
    r = max(r, R);
    int ans = 0;
    for (int i = l; i <= r; ++i) if (L[i]) ++ans;
    ans += (r - l + 1);
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}