#include <bits/stdc++.h>
using namespace std;
int N;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int ma = -2000000, mi = 2000000;
    int temp;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> temp;
        ma = max(ma, temp);
        mi = min(mi, temp);
    }
    cout << mi << " " << ma;
}