#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, K; cin >> N >> K;
    vector<int> line(100001, -1); line[N] = 0;
    deque<pair<int, int>> time = {{N, 0}};
    int place, value;
    while (!time.empty()) {
        place = time.front().first;
        value = time.front().second;
        time.pop_front();
        if (place + 1 <= 100000 && line[place + 1] == -1) {
            line[place + 1] = value + 1;
            time.push_back({place + 1, value + 1});
        }
        if (place - 1 >= 0 && line[place - 1] == -1) {
            line[place - 1] = value + 1;
            time.push_back({place - 1, value + 1});
        }
        if (place * 2 <= 100000 && line[place * 2] == -1) {
            line[place * 2] = value + 1;
            time.push_back({place * 2, value + 1});
        }
    }
    cout << line[K];
    return 0;
}