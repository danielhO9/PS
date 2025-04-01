#include <bits/stdc++.h>
using namespace std;

int M, N;
int arr[100000];
vector<int> change[100000];
unordered_map<int, int> m;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> M >> N;
    for (int i = 0; i < N; ++i) cin >> arr[i], --arr[i];
    int val = N;
    vector<int> ans;
    for (int i = 0; i < N; ++i) if ((arr[i] + 1) % M != 0) change[(arr[i] + 1) % M].push_back(arr[i] / M);
    for (int i = 0; i < N; ++i) ++m[arr[i] / M];
    ans.push_back(0); val = m.size();
    for (int i = 1; i < M; ++i) {
        for (auto j: change[i]) {
            --m[j]; if (m[j] == 0) m.erase(j);
            ++m[j - 1];
        }
        if (val > m.size()) {
            ans.clear(); ans.push_back(i);
            val = m.size();
        } else if (val == m.size()) ans.push_back(i);
    }
    cout << val << '\n';
    for (auto i: ans) cout << i + 1 << ' ';
}