#include <bits/stdc++.h>
using namespace std;
int N, M;
map<string, string> dict;

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M; string key, value;
    for (int i = 0; i < N; ++i) {
        cin >> key >> value;
        dict[key] = value;
    }
    for (int i = 0; i < M; ++i) {
        cin >> key;
        cout << dict[key] << "\n";
    }
}