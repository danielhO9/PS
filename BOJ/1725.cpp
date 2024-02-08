#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N;

ll solution(vector<ll>& h, ll left, ll right) {
    if (left == right) return h[left];
    ll mid = (left + right) / 2;
    ll ret = max(solution(h, left, mid), solution(h, mid + 1, right));
    ll lo = mid, hi = mid + 1;
    ll height = min(h[lo], h[hi]);
    ret = max(ret, height * 2);
    while (left < lo || hi < right) {
        if (hi < right && (left == lo || h[lo - 1] < h[hi + 1])) {
            ++hi;
            height = min(height, h[hi]);
        } else {
            --lo;
            height = min(height, h[lo]);
        }
        ret = max(ret, height * (hi - lo + 1));
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N; vector<ll> h(N);
    for (ll i = 0; i < N; ++i) cin >> h[i];
    cout << solution(h, 0, N - 1);
    return 0;
}