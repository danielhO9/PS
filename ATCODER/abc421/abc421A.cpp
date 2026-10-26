#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
string S[100];

void solve() {
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> S[i];
    int X; string Y; cin >> X >> Y;
    if (S[X - 1] == Y) cout << "Yes\n";
    else cout << "No\n";
    
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}