#include <bits/stdc++.h>
using namespace std;
int ind, v;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int temp;
    for (int i = 1; i <= 9; ++i) {
        cin >> temp;
        if (temp > v) {
            ind = i; v = temp;
        }
    }
    cout << v << "\n" << ind;
}