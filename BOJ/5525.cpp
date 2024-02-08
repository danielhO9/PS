#include <bits/stdc++.h>
using namespace std;
int N, M, ans; string P;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    cin >> M;
    cin >> P;
    string last = "";
    for (auto i: P) {
        if (i == 'I') {
            if (last.empty() || last.back() == 'O') {
                last.push_back('I');
            } else {
                if ((last.length() - 1) / 2 >= N) ans += (last.length() - 1) / 2 - N + 1;
                last = "I";
            }
        } else {
            if (!last.empty() && last.back() == 'I') {
                last.push_back('O');
            } else if (!last.empty()) {
                last.pop_back();
                if ((last.length() - 1) / 2 >= N) ans += (last.length() - 1) / 2 - N + 1;
                last = "";
            }
        }
    }
    if (!last.empty() && last.back() == 'O') last.pop_back();
    if (!last.empty() && (last.length() - 1) / 2 >= N) ans += (last.length() - 1) / 2 - N + 1;
    cout << ans;
}