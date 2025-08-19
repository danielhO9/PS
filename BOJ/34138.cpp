#include <bits/stdc++.h>
using namespace std;

int N, M;
char A[2000][2000];
int cache[2000][2000];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;
    vector<pair<int, int>> v;
    for (int i = 0; i < N; ++i) {
        string s; cin >> s;
        for (int j = 0; j < M; ++j) {
            A[i][j] = s[j];
            if (A[i][j] == 'X') {
                v.push_back(make_pair(i, j));
                cache[i][j] = 1;
            }
        }
    }
    for (int i = 0; i < min(N, M); ++i) {
        if (i == 0) {
            cout << v.size() << '\n';
            continue;
        }
        vector<pair<int, int>> nv;
        for (auto cor: v) {
            bool flag = true;
            if (cor.first + i < N && cor.second + i < M) flag = true;
            else flag = false;
            if (flag && (A[cor.first][cor.second + i] == 'X' || A[cor.first + i][cor.second] == 'X'
                || !cache[cor.first + 1][cor.second + 1])) flag = false;
            if (flag) nv.push_back(cor);
            else {
                cache[cor.first][cor.second] = 0;
            }
        }
        cout << nv.size() << '\n';
        swap(v, nv);
    }
}