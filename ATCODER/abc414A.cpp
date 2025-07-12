#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, L, R;
int X[100], Y[100];

void solve() {
    cin >> N >> L >> R;
    for (int i = 0; i < N; ++i) cin >> X[i] >> Y[i];
    int cnt = 0;
    for (int i = 0; i < N; ++i) if (X[i] <= L && R <= Y[i]) ++cnt;
    cout << cnt;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}