#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll sz = 531441;
vector<int> arr[531441];
string S;
int Q;
unordered_map<ll, int> m;

ll hashing(const string& s) {
    ll ret = 0, tmp = 1;
    for (auto i: s) {
        ret += (i - 'a' + 1) * tmp;
        tmp *= 27;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> S;
    for (int i = 0; i < S.size(); ++i) {
        int val = 0, tmp = 1;
        for (int j = 0; j < 4; ++j) if (i + j < S.size()) {
            val += (S[i + j] - 'a' + 1) * tmp;
            tmp *= 27;
            arr[val].push_back(i);
        }
    }

    cin >> Q;
    while (Q--) {
        string a, b; cin >> a >> b;
        ll ha = hashing(a), hb = hashing(b);
        if (m.find(ha * sz + hb) != m.end()) {
            cout << m[ha * sz + hb] << '\n';
            continue;
        }
        if (m.find(hb * sz + ha) != m.end()) {
            cout << m[hb * sz + ha] << '\n';
            continue;
        }
        if (arr[ha].size() > arr[hb].size()) {
            swap(a, b);
            swap(ha, hb);
        }
        int ans = INT32_MAX;
        for (auto i: arr[ha]) {
            int idx = lower_bound(arr[hb].begin(), arr[hb].end(), i) - arr[hb].begin();
            if (idx != arr[hb].size()) {
                int l = min(i, arr[hb][idx]);
                int r = max(i + a.size(), arr[hb][idx] + b.size());
                ans = min(ans, r - l);
            }
            if (idx != 0) {
                --idx;
                int l = min(i, arr[hb][idx]);
                int r = max(i + a.size(), arr[hb][idx] + b.size());
                ans = min(ans, r - l);
            }
        }
        if (ans == INT32_MAX) ans = -1;
        m[ha * sz + hb] = ans;
        cout << ans << '\n';
    }
}