#include <bits/stdc++.h>
using namespace std;
int s[80];

int main() {
    int T, ans; cin >> T; string temp;
    for (int i = 0; i < T; ++i) {
        cin >> temp; ans = 0;
        for (int j = 1; j <= temp.length(); ++j) {
            if (temp[j - 1] == 'X') s[j] = 0;
            else {
                s[j] = s[j - 1] + 1;
                ans += s[j];
            }
        }
        cout << ans << "\n";
    }
}