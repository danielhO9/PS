#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int N, L; cin >> N >> L;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {cin >> A[i];}
    deque<pair<int, int>> todo;
    for (int i = 0; i < N; ++i) {
        while (!todo.empty() && todo.front().first < i - L + 1) todo.pop_front();
        while (!todo.empty() && todo.back().second >= A[i]) todo.pop_back();
        todo.push_back({i, A[i]});
        cout << todo.front().second << " ";
    }
    return 0;
}