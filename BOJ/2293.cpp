#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int n, k;
LL cache[10001], coin[100];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> coin[i];
    cache[0] = 1;
    for (int i = 0; i < n; ++i) for (int j = coin[i]; j <= k; ++j) cache[j] += cache[j - coin[i]];
    cout << cache[k];
    return 0;
}