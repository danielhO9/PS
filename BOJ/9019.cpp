#include <bits/stdc++.h>
using namespace std;
int leng, temp;
bool visited[10000];

int D(int A) { return (A * 2) % 10000; }
int S(int A) { 
    if (A == 0) return 9999;
    else return A - 1;
}
int L(int A) { return (A % 1000) * 10 + (A / 1000); }
int R(int A) { return A / 10 + (A % 10) * 1000; }

deque<pair<int, string>> todo;
pair<int, string> now;

string solution(int A, int B) {
    todo.clear(); todo.shrink_to_fit();
    memset(visited, false, sizeof(visited));
    todo.push_back({A, ""});
    visited[A] = true;
    while (true) {
        now = todo.front(); todo.pop_front();
        if (now.first == B) return now.second;
        if (!visited[D(now.first)]) { todo.push_back({D(now.first), now.second + "D"}); visited[todo.back().first] = true;};
        if (!visited[S(now.first)]) { todo.push_back({S(now.first), now.second + "S"}); visited[todo.back().first] = true;};
        if (!visited[L(now.first)]) { todo.push_back({L(now.first), now.second + "L"}); visited[todo.back().first] = true;};
        if (!visited[R(now.first)]) { todo.push_back({R(now.first), now.second + "R"}); visited[todo.back().first] = true;};
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T; int x, y;
    for (int i = 0; i < T; ++i) {
        cin >> x >> y;
        cout << solution(x, y) << "\n";
    }
    return 0;
}