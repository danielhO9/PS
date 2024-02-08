#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int main() {
    LL S; cin >> S;
    LL N = 1;
    while ((N + 1) * (N + 1) + N + 1 <= 2 * S) ++N;
    cout << N;
}