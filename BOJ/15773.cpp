#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int N, ans;
vector<pair<LL, LL>> Q;
LL h;
priority_queue<LL> pos;

bool compare(const pair<LL, LL> &a, const pair<LL, LL> &b) {
    if (a.first + a.second == b.first + b.second) return a.second < b.second;
    return a.first + a.second > b.first + b.second;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N; LL L, D;
    for (int i = 0; i < N; ++i) {
        cin >> L >> D;
        Q.push_back({L, D});
    }
    sort(Q.begin(), Q.end(), compare);
    while (!Q.empty()) {
        if (h <= Q.back().first) {
            ++ans; h += Q.back().second; pos.push(Q.back().second);
        } else if (h - pos.top() <= Q.back().first && Q.back().second <= pos.top()) {
            h -= (pos.top() - Q.back().second); pos.pop(); pos.push(Q.back().second);
        }
        Q.pop_back();
    }
    cout << ans;
}