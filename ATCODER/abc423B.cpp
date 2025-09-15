#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
int L[101];
bool vis[101];

void solve() {
    cin >> N;
    for (int i = 1; i <= N; ++i) cin >> L[i];
    vis[0] = true;
    vis[N] = true;
    for (int i = 1; i <= N; ++i) {
        if (L[i]) break;
        else vis[i] = true;
    }
    for (int i = N; i >= 1; --i) {
        if (L[i]) break;
        else vis[i - 1] = true;
    }
    int ans = 0;
    for (int i = 0; i <= N; ++i) if (!vis[i]) ++ans;
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}