#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int ans = 0, temp;
    for (int i = 0; i < 5; ++i) {
        cin >> temp;
        ans += temp * temp;
        ans %= 10;
    }
    cout << ans;
}