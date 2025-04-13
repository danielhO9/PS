#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    set<int> s;
    map<int, int> m;
    int N; cin >> N;
    for (int i = 0; i < N; ++i) {
        int t; cin >> t;
        if (t == 1) {
            int x; cin >> x;
            if (s.find(x) != s.end()) continue;
            s.insert(x);
            auto itr = s.find(x);
            if (itr != s.begin()) ++m[*itr ^ *(prev(itr))];
            if (next(itr) != s.end()) ++m[*itr ^ *(next(itr))];
            if (itr != s.begin() && next(itr) != s.end()) {
                --m[*(prev(itr)) ^ *next(itr)];
                if (m[*(prev(itr)) ^ *next(itr)] == 0) m.erase(*(prev(itr)) ^ *next(itr));
            }
        } else if (t == 2) {
            int x; cin >> x;
            auto itr = s.find(x);
            if (itr != s.begin()) {
                --m[*itr ^ *(prev(itr))];
                if (m[*itr ^ *(prev(itr))] == 0) m.erase(*itr ^ *(prev(itr)));
            }
            if (next(itr) != s.end()) {
                --m[*itr ^ *(next(itr))];
                if (m[*itr ^ *(next(itr))] == 0) m.erase(*itr ^ *(next(itr)));
            }
            if (itr != s.begin() && next(itr) != s.end()) ++m[*(prev(itr)) ^ *next(itr)];
            s.erase(x);
        } else {
            cout << m.begin()->first << '\n';
        }
    }
}