#include <bits/stdc++.h>
using namespace std;

int power[3], len[3], ammo[3], cor = 0, L, Z[19], s = 0, sm = 0;
bool flag = false;

void dfs() {
    if (flag) return;
    if (cor >= s) return; // cor < s

    int mx = 0;
    for (int i = 0; i < 3; ++i) if (ammo[i] > 0) mx = max(mx, power[i] * (L - cor) * min(len[i], L - cor));
    if (sm > mx) return;

    assert(s != 0);
    assert(Z[s] > 0);
    assert(s <= L);
    assert(cor < s);
    assert(ammo[0] > 0);
    bool start1 = false;
    if (L - cor <= ammo[1]) start1 = true;
    for (int i = (start1 ? 1 : 0); i < 3; ++i) if (ammo[i] > 0) {
        if (flag) return;
        mx = 0;
        for (int j = 0; j < 3; ++j) if (ammo[j] > 0) mx = max(mx, power[j]);
        if (mx * (s - cor - 1) + power[i] < Z[s]) continue;
        if (L - cor <= ammo[2] && power[0] <= power[2] && i == 0) continue;
        if (L - cor <= ammo[2] && power[1] <= power[2] && i == 1) continue;
        
        vector< pair<int, int> > pz;
        int ps = s, psm = sm;
        for (int j = s; j < s + len[i]; ++j) {
            if (j > L) break;
            if (Z[j] == 0) continue;
            pz.push_back(make_pair(j, Z[j])); sm -= Z[j];
            Z[j] = max(Z[j] - power[i], 0); sm += Z[j];
        }
        --ammo[i];
        ++cor;
        s = 0;
        for (int j = ps; j <= L; ++j) {
            if (Z[j] > 0) { s = j; break; }
        }
        if (s == 0) {
            if (!flag) cout << "YES";
            flag = true;
        }
        assert(s == 0 || Z[s] > 0);
        if (s != 0) dfs();
        s = ps, sm = psm;
        for (auto [j, k]: pz) Z[j] = k;
        ++ammo[i];
        --cor;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> L >> power[0] >> power[1] >> ammo[1] >> power[2] >> len[2] >> ammo[2];
    ammo[0] = 20, len[0] = 1, len[1] = 1;
    assert(power[0] < power[1]);
    for (int i = 1; i <= L; ++i) cin >> Z[i], sm += Z[i];
    for (int i = 1; i <= L; ++i) if (Z[i] > 0) { s = i; break; }
    if (s == 0) {
        cout << "YES";
        return 0;
    }
    dfs();
    assert(cor == 0);
    if (!flag) cout << "NO";
}