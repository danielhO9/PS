#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int N; cin >> N;
    for (int i = 0; i < 9; ++i) {
        cout << N << " * " << i + 1 << " = " << N * (i + 1) << "\n";
    }
    return 0;
}