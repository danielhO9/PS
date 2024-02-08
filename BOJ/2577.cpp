#include <bits/stdc++.h>
using namespace std;
int ans[10];

int main() {
    int A, B, C; cin >> A >> B >> C;
    A *= B; A *= C;
    string temp; temp = to_string(A);
    for (auto i: temp) ++ans[i - '0'];
    for (auto i: ans) cout << i << "\n";
}