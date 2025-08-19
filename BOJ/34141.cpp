#include <bits/stdc++.h>
using namespace std;

int N;
int B[2000][2000];
vector<int> digit[10];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; ++i) {
        string s; cin >> s;
        for (int j = 0; j < N; ++j) B[i][j] = s[j] - '0';
    }
    int ans = 0;
    vector<int> cur;
    for (int r = N - 1; r >= 0; --r){
        if (r == N - 1) {
            for (int j = 0; j < N; ++j) cur.push_back(B[r][j]);
            continue;
        }
        // for (auto i: cur) cout << i << ' ';
        // cout << '\n';

        for (int i = 1; i <= 9; ++i) digit[i].clear();
        for (int i = 0; i < N; ++i) digit[B[r][i]].push_back(i);

        // same
        vector<int> nxt;
        vector<int> indices;
        int idx = 0;
        while (idx + 1 < cur.size()) {
            int tar = cur[idx];
            int last = indices.empty() ? -1 : indices.back();
            auto itr = upper_bound(digit[tar].begin(), digit[tar].end(), last);
            if (itr == digit[tar].end()) break;
            int tmp = *itr;
            if ((N - 1) - tmp + 1 + nxt.size() < cur.size()) break;
            indices.push_back(tmp);
            nxt.push_back(B[r][tmp]);
            ++idx;
        }

        // smaller
        while (idx >= 0) {
            int tar = cur[idx];
            int last = indices.empty() ? -1 : indices.back();
            bool flag = false;
            for (int num = tar - 1; num >= 1; --num) {
                auto itr = upper_bound(digit[num].begin(), digit[num].end(), last);
                if (itr == digit[num].end()) continue;
                int tmp = *itr;
                if ((N - 1) - tmp + 1 + nxt.size() < cur.size()) continue;
                flag = true;
                indices.push_back(tmp);
                nxt.push_back(B[r][tmp]);
                break;
            }
            if (flag) break;
            --idx;
            if (!nxt.empty()) {
                nxt.pop_back();
                indices.pop_back();
            }
        }

        // bigger
        int tar_len = cur.size();
        if (idx == -1) --tar_len;
        // cout << nxt.size() << ' ' << tar_len << '\n';
        while (nxt.size() < tar_len) {
            int last = indices.empty() ? -1 : indices.back();
            for (int num = 9; num >= 1; --num) {
                auto itr = upper_bound(digit[num].begin(), digit[num].end(), last);
                if (itr == digit[num].end()) continue;
                int tmp = *itr;
                if ((N - 1) - tmp + 1 + nxt.size() < tar_len) continue;
                indices.push_back(tmp);
                nxt.push_back(B[r][tmp]);
                // cout << tmp << '\n';
                break;
            }
        }
        ans += N - (int) nxt.size();
        swap(nxt, cur);
    }
    cout << ans;
}