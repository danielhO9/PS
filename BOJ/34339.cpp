#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
int A[100000];
pair<int, int> cache[101];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> A[i];
    for (int i = 0; i <= 100; ++i) cache[i] = make_pair(0, -1);
    cache[0] = make_pair(1, -1);
    ll ans = 0;
    for (int i = 0; i < N; ++i) {
        cache[0] = make_pair(1, i);
        for (int j = 99; j >= 0; --j) if (j + A[i] <= 100 && cache[j].first) {
            cache[j + A[i]].first = 1;
            cache[j + A[i]].second = max(cache[j + A[i]].second, cache[j].second);
        }
        if (cache[100].first) ans += (ll) cache[100].second + 1;
    }
    cout << ans;
}
