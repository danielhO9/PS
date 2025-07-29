#include <bits/stdc++.h>
using namespace std;

int n, k;
int C[100];
vector<int> s[100];
int idx[101];
vector<pair<int, int>> ans;

void move(int a, int b) {
    assert(!s[a].empty());
    assert(s[b].size() < C[b]);
    // cout << a << ' ' << b << '\n';
    ans.push_back(make_pair(a, b));
    int val = s[a].back();
    s[a].pop_back();
    idx[val] = b;
    s[b].push_back(val);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    for (int i = 0; i < k; ++i) {
        cin >> C[i];
        for (int j = 0; j < C[i]; ++j) {
            int val; cin >> val;
            if (val == 0) continue;
            s[i].push_back(val);
            idx[val] = i;
        }
    }
    for (int i = 1; i <= n; ++i) {
        // cout << "cur: " << i << '\n';
        // for (int j = 0; j < k; ++j) {
        //     for (auto l: s[j])cout << l << ' ';
        //     cout << '\n';
        // }
        int tar = i == 1 ? 0 : idx[i - 1];
        if (i != 1 && s[tar].size() == C[tar] && s[tar].back() == i - 1) ++tar;
        int cur = idx[i];
        int mn = 101, tmp = -1;
        for (int j = 0; j < k; ++j) if (j != tar && j != cur) {
            if (mn > C[j]) {
                mn = C[j];
                tmp = j;
            }
        }

        // cur 비우기
        for (int j = 0; j < k; ++j) if (j != cur) {
            while (s[cur].back() != i && s[j].size() < C[j]) {
                move(cur, j);
            }
        }
        // tmp 채우기
        int movedVal= 0;
        int movedIdx = 0;
        if (s[tmp].size() == C[tmp]) {
            for (int j = 0; j < k; ++j) if (j != tmp && j != cur && s[j].size() < C[j]) {
                if (s[tmp].back() > i) {
                    move(tmp, j);
                    break;
                }
                movedVal = s[tmp].back();
                movedIdx = j;
                move(tmp, j);
                break;
            }
        }
        for (int j = 0; j < k; ++j) if (j != tmp && j != cur) {
            while (s[j].size() > 0 && s[j].back() > i && s[tmp].size() + 1 < C[tmp]) {
                move(j, tmp);
            }
        }
        // cur -> tmp
        move(cur, tmp);
        if (movedVal && movedIdx == tar) {
            for (int j = 0; j < k; ++j) if (j != tmp && j != tar && s[j].size() < C[j]) {
                movedIdx = j;
                move(tar, j);
                break;
            }
        }

        // tar 비우기
        for (int j = 0; j < k; ++j) if (j != tmp && j != tar) {
            while (s[j].size() < C[j]) {
                if (s[tar].empty() || s[tar].back() < i) break;
                move(tar, j);
                // re.push(make_pair(tar, j));
            }
        }
        move(tmp, tar);
        if (movedVal) {
            for (int j = 0; j < k; ++j) if (j != movedIdx && j != tmp) {
                while (s[j].size() < C[j] && s[movedIdx].back() != movedVal) {
                    move(movedIdx, j);
                }
            }
            assert(s[movedIdx].back() == movedVal);
            move(movedIdx, tmp);
        }
    }
    for (auto i: ans) {
        cout << i.first + 1 << ' ' << i.second + 1 << '\n';
    }
    cout << 0 << ' ' << 0 << '\n';
    // for (int i = 0; i < k; ++i) {
    //     for (auto j: s[i]) cout << j << ' ';
    //     cout << '\n';
    // }
}