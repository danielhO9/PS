#include <bits/stdc++.h>
using namespace std;
int N;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N; string temp; int ans = 0; cin >> temp;
    for (int i = 0; i < N; ++i) {
        ans += temp[i] - '0';
    }
    cout << ans;
}