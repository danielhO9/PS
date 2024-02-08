#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;
    long long a, b;
    deque<pair<long long, long long>> arr;
    for (int i = 0; i < N; ++i) {
        cin >> a >> b;
        arr.push_back({b, a});
    }
    sort(arr.begin(), arr.end());
    long long time = 0; int answer = 0;
    while (!arr.empty()) {
        if (time <= arr.front().second) {
            ++answer;
            time = arr.front().first;
        }
        arr.pop_front();
    }
    cout << answer;
    return 0;
}