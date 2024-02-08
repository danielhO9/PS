#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll A, B, V; cin >> A >> B >> V;
    V -= A;
    if (V % (A - B) == 0) cout << V / (A - B) + 1;
    else cout << V / (A - B) + 2;

    return 0;
}