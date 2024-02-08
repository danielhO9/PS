#include <bits/stdc++.h>
using namespace std;
vector<int> times = {1};
map<pair<int, int>, int> memo;

int solution(int l, int r) {
    if (memo.find({l, r}) != memo.end()) { return memo[{l, r}]; }
    int li, ri, ret = 0;
    for (int i = 0; i < 31; ++i) {
        if (times[i] - 1 <= l) li = i;
        if (times[i] - 1 <= r) ri = i;
    }
    if (ri - li == 0) {
        ret = max(ret, li + solution(l - times[li] + 1, r - times[ri] + 1));
    } else {
        if (ri - li == 1) ret = max(ret, li + solution(l - times[li] + 1, times[li] - 1));
        else ret = max(ret, ((ri - 1) * ri) / 2 + 1);
        ret = max(ret, ri + solution(0, r - times[ri] + 1));
    }
    memo[{l, r}] = ret;
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    for (int i = 0; i < 30; ++i) times.push_back(times.back() * 2);
    memo[{0, 0}] = 0; memo[{1, 1}] = 1;
    int x, y, T;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        cin >> x >> y;
        cout << solution(x, y) << "\n";
    }
    return 0;
}