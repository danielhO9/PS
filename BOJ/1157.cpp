#include <bits/stdc++.h>
using namespace std;
map<char, int> m; char ans; int cnt;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    string temp; cin >> temp;
    for (auto i: temp) ++m[toupper(i)];
    for (auto [a, b]: m) {
        if (cnt == b) ans = '?';
        else if (cnt < b) {
            cnt = b; ans = a;
        }
    } 
    cout << ans;
}