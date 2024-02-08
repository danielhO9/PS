#include <bits/stdc++.h>
using namespace std;
map<string, int> clothes; int n, ans;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T; string temp, type;
    for (int i = 0; i < T; ++i) {
        cin >> n;
        for (int j = 0; j < n; ++j) {
            cin >> temp >> type;
            ++clothes[type];
        }
        if (n == 0) cout << 0 << "\n";
        else {
            ans = 1;
            for (auto [t, c]: clothes) ans *= (c + 1);
            cout << ans - 1 << "\n";
        }
        clothes.clear();
    }
}