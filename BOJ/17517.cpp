#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
 
int N, p = 1;
vector<pair<pair<int, int>, LL>> bridge;
vector<LL> temp;
LL ret;
 
bool compare(const pair<pair<int, int>, LL>& l, const pair<pair<int, int>, LL>& r) {
    if (l.first.first == r.first.first) return l.first.second > r.first.second;
    return l.first.first < r.first.first;
}
 
void combine(priority_queue<LL>& v, priority_queue<LL>& u) {
    if (v.size() < u.size()) swap(v, u);
    while (!u.empty()) {
        temp.push_back(v.top() + u.top());
        v.pop(); u.pop();
    }
    while (!temp.empty()) {
        v.push(temp.back());
        temp.pop_back();
    }
}
 
priority_queue<LL> dfs(int v) {
    priority_queue<LL> ans;
    while (p < N + 1 && bridge[v].first.first <= bridge[p].first.first && bridge[p].first.second <= bridge[v].first.second) {
        ++p; auto c = dfs(p - 1);
        combine(ans, c);
    }
    ans.push(bridge[v].second);
    return ans;
}
 
 
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N; int S, E; LL V;
    for (int i = 0; i < N; ++i) {
        cin >> S >> E >> V;
        bridge.push_back({{S, E}, V});
    }
    bridge.push_back({{0, 1e6}, 0});
    sort(bridge.begin(), bridge.end(), compare);
    auto ans = dfs(0);
    for (int i = 0; i < N; ++i) {
        if (ans.empty()) cout << ret << " ";
        else {
            ret += ans.top();
            cout << ret << " ";
            ans.pop();
        }
    }
}