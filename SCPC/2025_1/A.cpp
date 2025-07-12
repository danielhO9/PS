#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N;
ll arr[100000];
ll cnt[3];

void solve() {
    cin >> N;
    for (ll i = 0; i < N; ++i) cin >> arr[i];
    memset(cnt, 0, sizeof(cnt));
    for (ll i = 0; i < N; ++i) {
        bool flag = true;
        if (arr[i] == 500) ++cnt[0];
        else if (arr[i] == 1000) {
            if (cnt[0] < 1) flag = false;
            else {
                --cnt[0];
                ++cnt[1];
            }
        } else {
            if (cnt[0] >= 1 && cnt[0] * 500 + cnt[1] * 1000 >= 4500) {
                ll tmp = min(cnt[1], 4ll);
                cnt[1] -= tmp;
                tmp = 4500 - 1000 * tmp;
                tmp /= 500;
                cnt[0] -= tmp;
            } else flag = false;
            
        }
        if (!flag) {
            cout << i << '\n';
            return;
        }
    }
    cout << N << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll t; cin >> t;
    for (ll i = 1; i <= t; ++i) {
        cout << "Case #" << i << '\n';
        solve();
    }
}