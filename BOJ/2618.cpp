#include <bits/stdc++.h>
using namespace std;
int N, W;
pair<int, int> event[1001];
pair<int, int> cache[1001][1001];

int getDistance(int start, int end, int id) {
    if (start == 0) {
        if (id == 0) return abs(1 - event[end].first) + abs(1 - event[end].second);
        else return abs(N - event[end].first) + abs(N - event[end].second);
    } else return abs(event[start].first - event[end].first) + abs(event[start].second - event[end].second);
}

int doEvent(int p1, int p2) {
    if (p1 == W || p2 == W) return 0;
    pair<int, int>& ret = cache[p1][p2];
    if (ret.first != -1) return ret.first;
    int num = max(p1, p2) + 1;
    ret.first = min(doEvent(num, p2) + getDistance(p1, num, 0), doEvent(p1, num) + getDistance(p2, num, 1));
    if (doEvent(num, p2) + getDistance(p1, num, 0) < doEvent(p1, num) + getDistance(p2, num, 1)) ret.second = 0;
    else ret.second = 1;
    return ret.first;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N; cin >> W;
    for (int i = 1; i <= W; ++i) { cin >> event[i].first >> event[i].second; }
    for (int i = 0; i <= W; ++i) for (int j = 0; j <= W; ++j) cache[i][j] = {-1, -1};
    cout << doEvent(0, 0) << "\n"; int temp, p1 = 0, p2 = 0;
    for (int i = 1; i <= W; ++i) {
        temp = cache[p1][p2].second;
        cout << temp + 1 << "\n";
        if (temp == 0) p1 = i;
        else p2 = i;
    }
    return 0;
}