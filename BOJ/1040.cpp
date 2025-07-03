#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    string S; int K; cin >> S >> K;
    int used = 0;
    for (auto i: S) used |= (1 << (i - '0'));
    int cnt = 0;
    for (int i = 0; i < 10; ++i) if ((used >> i) & 1) ++cnt;
    if (cnt == K) {
        cout << S;
        return 0;
    }
    while (S.size() < 19) S = '0' + S;
    int s;
    for (int i = 0; i < 19; ++i) if (S[i] != '0') {
        s = i;
        break;
    }
    for (int i = 18; i >= 0; --i) {
        for (int l = 1; l < 10; ++l) {
            used = 0, cnt = 0;
            for (int j = s; j < i; ++j) used |= (1 << (S[j] - '0'));
            if (S[i] + l > '9') continue;
            used |= (1 << (S[i] + l - '0'));
            for (int j = 0; j < 10; ++j) if ((used >> j) & 1) ++cnt;
            if (cnt > K) continue;
            int muse = K - cnt;
            int nused = (1 << 10) - 1 - used;
            int rem = 18 - i;
            if (rem < muse) continue;
            string ans;
            for (int j = s; j < i; ++j) ans += S[j];
            ans += (S[i] + l);
            vector<int> tmp;
            for (int j = 0; j < 10; ++j) if ((nused >> j) & 1) {
                if (tmp.size() < muse) tmp.push_back(j);
                else nused ^= (1 << j);
            }
            for (int j = 0; j < 10; ++j) if ((used >> j) & 1) {
                tmp.push_back(j);
            }
            sort(tmp.begin(), tmp.end());
            for (int j = 0; j < rem - muse; ++j) ans += (tmp[0] + '0');
            for (int j = 0; j < 10; ++j) if ((nused >> j) & 1) {
                ans += (j + '0');
            }
            cout << ans;
            return 0;
        }
    }
}