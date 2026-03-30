#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int N; cin >> N;
    vector<pair<int, int>> v(N);
    for (int i = 0; i < N; ++i) cin >> v[i].first >> v[i].second;
    sort(v.begin(), v.end());
    multiset<int> s;
    for (auto i: v) {
        if (s.empty() || *s.begin() > i.first) {
            s.insert(i.second);
        } else {
            s.erase(s.find(*s.begin()));
            s.insert(i.second);
        }
    }
    cout << s.size();
}