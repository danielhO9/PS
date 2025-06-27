#include <bits/stdc++.h>
using namespace std;

/*
Ti, Tj
Si, Sj
Ti * Sj < Tj * Si

*/

struct Query {
    int T, S, idx;
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int N; cin >> N;
    vector<Query> v(N);
    for (int i = 0; i < N; ++i) {
        cin >> v[i].T >> v[i].S;
        v[i].idx = i;
    }
    sort(v.begin(), v.end(), [](const Query& a, const Query& b) {
        if (a.T * b.S == b.T * a.S) return a.idx < b.idx;
        return a.T * b.S < b.T * a.S;
    });
    for (int i = 0; i < N; ++i) cout << v[i].idx + 1 << ' ';
}