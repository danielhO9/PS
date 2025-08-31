#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll dy[4] = {-1, 1, 0, 0};
ll dx[4] = {0, 0, -1, 1};

ll tcor[2], acor[2];
ll N, M, L;
vector<pair<int, ll>> t, a;
ll ans = 0;

ll dis(ll x, ll y, ll tx, ll ty) {
    return abs(x - tx) + abs(y - ty);
}

void simulate(int i, int j) {
    // cout << tcor[0] << ' ' << tcor[1] << ' ';
    // cout << acor[0] << ' ' << acor[1] << '\n';
    if (i == t.size()) return;
    ll d = min(t[i].second, a[j].second);
    // cout << d << '\n';
    assert(d != 0);

    if (t[i].first == a[j].first) {
        if (tcor[0] == acor[0] && tcor[1] == acor[1]) ans += d;
    } else {
        if ((t[i].first <= 1) == (a[j].first <= 1)) {
            if (t[i].first <= 1) {
                if (tcor[1] == acor[1]) {
                    if ((t[i].first == 0 && tcor[0] > acor[0]) || (t[i].first == 1 && tcor[0] < acor[0])) {
                        ll dis = abs(tcor[0] - acor[0]);
                        if (dis % 2 == 0 && dis / 2 <= d) ++ans;
                    }
                }
            } else {
                if (tcor[0] == acor[0]) {
                    if ((t[i].first == 2 && tcor[1] > acor[1]) || (t[i].first == 3 && tcor[1] < acor[1])) {
                        ll dis = abs(tcor[1] - acor[1]);
                        if (dis % 2 == 0 && dis / 2 <= d) ++ans;
                    }
                }
            }
        } else {
            ll tar[2];
            if (t[i].first <= 1) {
                tar[0] = acor[0];
                tar[1] = tcor[1];
            } else {
                tar[0] = tcor[0];
                tar[1] = acor[1];
            }
            ll d1 = dis(tcor[0], tcor[1], tar[0], tar[1]);
            ll d2 = dis(acor[0], acor[1], tar[0], tar[1]);
            if (d1 == d2 && d1 <= d) {
                if (((t[i].first == 0 && tar[0] < tcor[0]) || (t[i].first == 1 && tar[0] > tcor[0])
                    || (t[i].first == 2 && tar[1] < tcor[1]) || (t[i].first == 3 && tar[1] > tcor[1])) &&
                    ((a[j].first == 0 && tar[0] < acor[0]) || (a[j].first == 1 && tar[0] > acor[0])
                    || (a[j].first == 2 && tar[1] < acor[1]) || (a[j].first == 3 && tar[1] > acor[1]))) ++ans;
            }
        }
    }

    tcor[0] += dy[t[i].first] * d;
    tcor[1] += dx[t[i].first] * d;
    acor[0] += dy[a[j].first] * d;
    acor[1] += dx[a[j].first] * d;
    t[i].second -= d;
    a[j].second -= d;
    
    int ni = i, nj = j;
    if (t[i].second == 0) ++ni;
    if (a[j].second == 0) ++nj;
    
    simulate(ni, nj);
}

void solve() {
    cin >> tcor[0] >> tcor[1] >> acor[0] >> acor[1];
    cin >> N >> M >> L;
    for (int i = 0; i < M; ++i) {
        char c; ll val; cin >> c >> val;
        if (c == 'U') t.push_back(make_pair(0, val));
        else if (c == 'D') t.push_back(make_pair(1, val));
        else if (c == 'L') t.push_back(make_pair(2, val));
        else t.push_back(make_pair(3, val));
    }
    for (int i = 0; i < L; ++i) {
        char c; ll val; cin >> c >> val;
        if (c == 'U') a.push_back(make_pair(0, val));
        else if (c == 'D') a.push_back(make_pair(1, val));
        else if (c == 'L') a.push_back(make_pair(2, val));
        else a.push_back(make_pair(3, val));
    }
    // if (tcor[0] == acor[0] && tcor[1] == acor[1]) ++ans;
    simulate(0, 0);
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}