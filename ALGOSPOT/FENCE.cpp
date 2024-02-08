#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll solution(vector<ll>& h, ll left, ll right) {
    if (left == right) return h[left];
    ll mid = (left + right) / 2;
    ll ret = max(solution(h, left, mid), solution(h, mid + 1, right));
    ll lo = mid, hi = mid + 1;
    ll height = min(h[lo], h[hi]);
    ret = max(ret, height * 2);
    while (left < lo || hi < right) {
        if (hi < right && (lo == left || h[lo - 1] < h[hi + 1])) {
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
    ll C; cin >> C;
    ll N;
    for (ll i = 0; i < C; ++i) {
        cin >> N; vector<ll> h(N);
        for (ll j = 0; j < N; ++j) cin >> h[j];
        cout << solution(h, 0, N - 1) << "\n";
    }

    return 0;
}