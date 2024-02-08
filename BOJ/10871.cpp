#include <bits/stdc++.h>
using namespace std;
int N, X;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> X; int temp;
    for (int i = 0; i < N; ++i) {
        cin >> temp;
        if (temp < X) cout << temp << " ";
    }
}