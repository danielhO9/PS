#include <bits/stdc++.h>
using namespace std;

int cache[100000][2];
const int MIN = -1e6;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        for (int i = 0; i < s.size(); ++i) {
            if (i == 0) {
                cache[i][0] = 1;
                cache[i][1] = MIN;
            }
            else if (i == 1) {
                if (s[i] != s[i - 1]) {
                    cache[i][0] = 2;
                    cache[i][1] = 1;
                } else {
                    cache[i][0] = MIN;
                    cache[i][1] = 1;
                }
            } else {
                cache[i][0] = cache[i - 1][1] + 1;
                if (s[i] != s[i - 1]) cache[i][0] = max(cache[i][0], cache[i - 1][0] + 1);
                cache[i][1] = cache[i - 2][0] + 1;
                if (i >= 3 && (s[i] != s[i - 2] || s[i - 1] != s[i - 3])) {
                    cache[i][1] = max(cache[i][1], cache[i - 2][1] + 1);
                }
            }
        }
        cout << max(cache[(int) s.size() - 1][0], cache[(int) s.size() - 1][1]) << '\n';
    }
}