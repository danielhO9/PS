#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int N, M; cin >> N >> M;
    map<string, int> people;
    string temp;
    for (int i = 0; i < N + M; ++i) {
        cin >> temp;
        people[temp]++;
    }
    int answer = 0;
    for (auto ite = people.begin(); ite != people.end(); ++ite) {
        if (ite->second == 2) answer += 1;
    }
    cout << answer << "\n";
    for (auto ite = people.begin(); ite != people.end(); ++ite) {
        if (ite->second == 2) cout << ite->first << "\n";
    }
    return 0;
}