#include <bits/stdc++.h>
using namespace std;

int Wx, Wy, sx, sy, tx, ty, n;
int mid;
vector<vector<int>> min_distance(1001, vector<int>(1001, 0));
// y 기준
vector<deque<int>> smell(1001, deque<int>(0));

struct Line {
    int slope, y_value;
    mutable double meet;

    bool operator < (int x) const {return meet < x;}
};

struct LineContainer: vector<Line> {
    double meetPoint(iterator a, iterator b) {
        return ((*b).y_value - (*a).y_value) / static_cast<double>((*a).slope - (*b).slope);
    }

    bool removeNext(iterator a) {
        a->meet = meetPoint(a, next(a));
        return a->meet >= next(a)->meet;
    }

    void add(int slope, int y_value) {
        push_back({slope, y_value, 1001.0}); auto ite = end() - 1;
        if (ite != begin() && removeNext(--ite)) {erase(next(ite)); removeNext(ite);}
        else {while (ite != begin() && removeNext(--ite)) {erase(next(ite)); removeNext(ite);}}
    }
};

bool visited[1001][1001];
deque<pair<int, int>> todo;
vector<pair<int, int>> way = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
pair<int, int> now;
void bfs(int value) {
    memset(visited, false, sizeof(visited));
    todo = {{sy, sx}}; visited[sy][sx] = true;
    while (!todo.empty()) {
        now = todo.front(); todo.pop_front();
        for (pair<int, int> element: way) {
            if (1 <= now.first + element.first && now.first + element.first <= Wy && 1 <= now.second + element.second && now.second + element.second <= Wx
            && !visited[now.first + element.first][now.second + element.second]
            && min_distance[now.first + element.first][now.second + element.second] >= value) {
                visited[now.first + element.first][now.second + element.second] = true;
                todo.push_back({now.first + element.first, now.second + element.second});
            }
        }
    }

}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    cin >> Wx >> Wy;
    cin >> sx >> sy >> tx >> ty;
    cin >> n;
    int x, y;
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        smell[y].push_back(x);
    }
    for (int i = 1; i <= Wy; ++i) sort(smell[i].begin(), smell[i].end());

    vector<LineContainer> lines(1001);
    for (int i = 1; i <= Wx; ++i) {
        for (int j = 1; j <= Wy; ++j) {
            if (smell[j].size() >= 2 && abs(i - smell[j][0]) >= abs(i - smell[j][1])) smell[j].pop_front();
            if (!smell[j].empty()) lines[i].add((-2) * j, j * j + smell[j].front() * smell[j].front() - 2 * smell[j].front() * i + i * i);
        }
    }
    for (int i = 1; i <= Wx; ++i) {
        for (int j = 1; j <= Wy; ++j) {
            Line line = *lower_bound(lines[i].begin(), lines[i].end(), j);
            min_distance[j][i] = line.slope * j + line.y_value + j * j;
        }
    }

    int start = 0, end = min_distance[sy][sx];
    mid = (start + end) % 2 == 0 ? (start + end) / 2 : (start + end) / 2 + 1;
    while (start < end) {
        bfs(mid);
        if (visited[ty][tx]) start = mid;
        else end = mid - 1;
        mid = (start + end) % 2 == 0 ? (start + end) / 2 : (start + end) / 2 + 1;
    }
    cout << mid;

    return 0;
}