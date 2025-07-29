#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int cnt = 0;

bool isSky(int w, ll h) {
    cout << "? " << w << ' ' << h << '\n';
    cout.flush();
    string s; cin >> s;
    ++cnt;
    return s == "sky";
}

ll w, h;
random_device rd;
mt19937 g(rd());

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> w >> h;
    vector<ll> arr; for (int i = 1; i <= w; ++i) arr.push_back(i);
    shuffle(arr.begin(), arr.end(), g);
    ll ans = 0;
    int idx = 1;
    for (auto i: arr) {
        if (ans == h) break;
        if (isSky(i, ans + 1)) continue;
        ll l = ans + 1, r = h + 1, mid;
        while (l + 1 < r) {
            mid = (l + r) / 2;
            if (isSky(i, mid)) r = mid;
            else l = mid;
        }
        ans = l;
        idx = i;
    }
    cout << "! " << idx << ' ' << ans << '\n';
    cout.flush();
}