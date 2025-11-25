#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N;
ll A[2000];
vector<ll> v;
ll cache[4001][4001];

ll matchCache(int l, int r) {
    if (l > r) return 0;
    if (l == r) return v[l];
    ll& ret = cache[l][r];
    if (ret != -1) return ret;
    ll ret1 = v[l];
    if (v[l + 1] < v[r]) ret1 += matchCache(l + 1, r - 1);
    else ret1 += matchCache(l + 2, r);

    ll ret2 = v[r];
    if (v[l] < v[r - 1]) ret2 += matchCache(l, r - 2);
    else ret2 += matchCache(l + 1, r - 1);
    return ret = max(ret1, ret2);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    memset(cache, -1, sizeof(cache));
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> A[i];
    if (N == 1) {
        cout << A[0];
        return 0;
    }
    for (int i = 0; i < N; ++i) v.push_back(A[i]);
    for (int i = 0; i < N; ++i) v.push_back(A[i]);
    ll ans = LLONG_MIN;
    for (int i = 0; i < N; ++i) ans = max(ans, matchCache(i, i + N - 1));
    cout << ans;
}