#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    while (true) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == 0) break;
        if (a * a + b * b == c * c || c * c + b * b == a * a || a * a + c * c == b * b) cout << "right" << "\n";
        else cout << "wrong" << "\n";
    }
    return 0;
}
