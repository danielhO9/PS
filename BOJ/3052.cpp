#include <bits/stdc++.h>
using namespace std;
set<int> S;

int main() {
    int temp;
    for (int i = 0; i < 10; ++i) {
        cin >> temp;
        S.insert(temp % 42);
    }
    cout << S.size();
}