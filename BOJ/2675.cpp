#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; int c; string temp;
    for (int i = 0; i < t; ++i) {
        cin >> c >> temp;
        for (auto j: temp) {
            for (int k = 0; k < c; ++k) cout << j;
        }
        cout << "\n";
    }
}