#include <bits/stdc++.h>
using namespace std;

int N;
deque<int> dq[2];
int cnt[2][101], one[2];
vector<pair<int, int>> ans;

void f(int l, int r) {
    ans.push_back(make_pair(l, r));
    assert(ans.size() <= 200000);
    assert(dq[r].size() <= N);

    assert(!dq[l].empty());
    int x = dq[l].front();
    ++cnt[r][x]; --cnt[l][x];
    
    if (l != r) {
        if (cnt[r][x] == 1) ++one[r];
        else {
            assert(cnt[r][x] == 2);
            --one[r];
        }

        if (cnt[l][x] == 1) ++one[l];
        else {
            assert(cnt[l][x] == 0);
            --one[l];
        }
    
    }
    dq[r].push_back(x);
    dq[l].pop_front();
    assert(dq[r].size() <= N + 1);
    assert(dq[l].size() <= N + 1);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 0; i < 2; ++i) {
        int n; cin >> n;
        for (int j = 0; j < n; ++j) {
            int t; cin >> t;
            dq[i].push_back(t);
        }
    }

    for (int i = 0; i < 2; ++i) for (auto j: dq[i]) ++cnt[i][j];

    for (int i = 0; i < 2; ++i) {
        for (int j = 1; j <= N; ++j) if (cnt[i][j] == 1) ++one[i];
    }

    if (dq[0].size() < dq[1].size()) f(1, 0);
    if (dq[1].size() < dq[0].size()) f(0, 1);
    assert(dq[0].size() == N);

    while (one[0] < N || one[1] < N) {
        while (cnt[0][dq[0].front()] == 1) f(0, 0);
        while (cnt[1][dq[1].front()] == 1) f(1, 1);
        f(0, 1);
        f(1, 0);
        assert(dq[0].size() == N);
    }

    for (int i = 0; i < 2; ++i) {
        for (int j = 2; j <= N; ++j) {
            while (dq[i].front() != j) f(i, i);
            while (dq[i ^ 1].front() != j) f(i ^ 1, i ^ 1);

            f(i, i ^ 1);

            while (dq[i].back() != j - 1) f(i, i);

            f(i ^ 1, i);
        }
        
    }
    for (int i = 0; i < 2; ++i) while (dq[i].front() != 1) f(i, i);

    for (int i = 0; i < 2; ++i) {
        assert(dq[i].size() == N);
        for (int j = 0; j < N; ++j) assert(dq[i][j] == j + 1);
    }
    cout << ans.size() << '\n';
    for (auto i: ans) cout << i.first + 1 << ' ' << i.second + 1 << '\n';
}