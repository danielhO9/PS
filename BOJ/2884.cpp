#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int H, M; cin >> H >> M;
    M -= 45;
    if (M < 0) { H -= 1; M += 60; }
    if (H < 0) H += 24;
    cout << H << " " << M;
}