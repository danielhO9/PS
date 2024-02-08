#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int N, M; cin >> N >> M;
    string temp;
    map<string, int> number; vector<string> dogam; dogam.push_back("");
    for (int i = 1; i < N + 1; ++i) {
        cin >> temp;
        number.insert({temp, i});
        dogam.push_back(temp);
    }
    for (int i = 0; i < M; ++i) {
        cin >> temp;
        if (int(temp[0]) < 58) cout << dogam[stoi(temp)] << "\n";
        else cout << number[temp] << "\n";
    }

    return 0;
}