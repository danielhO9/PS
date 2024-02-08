#include <bits/stdc++.h>
using namespace std;
int ans[26];

int main() {
    string temp; cin >> temp;
    memset(ans, -1, sizeof(ans));
    for (int i = 0; i < temp.length(); ++i) {
        if (ans[temp[i] - 'a'] == -1) ans[temp[i] - 'a'] = i;
    }
    for (auto i: ans) cout << i << " ";
}